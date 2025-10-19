
#include "Characters/PRCharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "PRTypes.h"
#include "Components/PRStatsComponent.h"
#include <Player/PRPlayerState.h>
#include "Engine/DamageEvents.h" 
#include <AI/PRAIBase.h>
#include <Kismet/GameplayStatics.h>

APRCharacterBase::APRCharacterBase()
{

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName); // Attach the camera to the end of the boom
	CameraComp->bUsePawnControlRotation = false; // Let the boom control the camera's rotation

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	bUseControllerRotationYaw = false; // ...and doesn't directly follow the camera's yaw. This gives a nice third-person feel.

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// DefaultMappingContext'i header'da bir UPROPERTY olarak tanýmlaman gerekir.
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

UPRStatsComponent* APRCharacterBase::GetStatsComponent() const
{
	// First, check if we've already found and cached it.
	if (CachedStatsComponent)
	{
		return CachedStatsComponent;
	}

	// If not, get it from the PlayerState. This is player-specific logic.
	if (APRPlayerState* PS = GetPlayerState<APRPlayerState>())
	{
		// Cache the result so we don't have to do this lookup again.
		CachedStatsComponent = PS->StatsComponent;
		return CachedStatsComponent;
	}

	// As a last resort, call the base class's implementation (which looks on the actor itself).
	// This is good practice for safety, but for a player, it should always be on the PlayerState.
	return Super::GetStatsComponent();
}

void APRCharacterBase::BeginPlay()
{
	Super::BeginPlay(); 

	InitializeFromDataAsset();
	InitializeInput();

	if (UPRStatsComponent* MyStatsComponent = GetStatsComponent())
	{
		// Bind to the virtual functions inherited from EntityBase.
		MyStatsComponent->OnHealthChangedDelegate.AddDynamic(this, &APRCharacterBase::OnHealthChanged);
		MyStatsComponent->OnDeathDelegate.AddDynamic(this, &APRCharacterBase::OnDeath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterBase %s could not find its StatsComponent!"), *GetName());
	}
}

void APRCharacterBase::InitializeFromDataAsset()
{
	UPRStatsComponent* MyStatsComponent = GetStatsComponent();

	if (!MyStatsComponent)
	{
		return;
	}

	// Check if the CharacterDefinition is valid
	if (CharacterDefinition)
	{
		// 1. Set the Skeletal Mesh
		if (GetMesh() && CharacterDefinition->CharacterMesh)
		{
			GetMesh()->SetSkeletalMesh(CharacterDefinition->CharacterMesh);
		}

		// 2. Initialize Stats Component with the correct Data Table
		if (MyStatsComponent && CharacterDefinition->StartingStatsTable)
		{
			MyStatsComponent->InitializeWithDataTable(CharacterDefinition->StartingStatsTable);
		}

		// 3. (Future) Set Animation Blueprint
		// if (GetMesh() && CharacterDefinition->AnimationBlueprintClass)
		// {
		// 	GetMesh()->SetAnimInstanceClass(CharacterDefinition->AnimationBlueprintClass);
		// }
	}
	else
	{
		// Log an error if no Data Asset is assigned. This helps debugging.
		UE_LOG(LogTemp, Error, TEXT("Character %s has NO CharacterDefinition assigned!"), *GetName());
	}
}

void APRCharacterBase::InitializeInput()
{
	// Make sure we are dealing with a player controller
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add the mapping context. The 0 is the priority.
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void APRCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Cast to the Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind the Input Actions
		// Bind a function that takes a FInputActionValue (a flexible struct)
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APRCharacterBase::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APRCharacterBase::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(DebugDamageAction, ETriggerEvent::Started, this, &APRCharacterBase::TakeDebugDamage);

	}

	// We will add Action bindings for Jump, Dash, Ability etc. here later.
}

void APRCharacterBase::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}


void APRCharacterBase::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APRCharacterBase::TakeDebugDamage()
{
	// Simple sphere trace in front of the character to find an enemy to damage
	FVector Start = GetActorLocation();
	FVector End = Start + (GetActorForwardVector() * 200.0f);
	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(100.0f);

	bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, Sphere);

	if (bHit)
	{
		for (auto& Hit : HitResults)
		{
			// We still cast to AIBase to make sure we are not damaging another player or ourselves.
			if (APRAIBase* AI = Cast<APRAIBase>(Hit.GetActor()))
			{
				// --- We override applydamage ---
				UGameplayStatics::ApplyDamage(
					AI,       // The actor that will take damage
					50.f,     // The base damage amount
					GetController(), // The controller that instigated the damage
					this,     // The actor that caused the damage
					nullptr   // The damage type class (can be null for generic damage)
				);

				UE_LOG(LogTemp, Warning, TEXT("Applied 50 damage to %s"), *AI->GetName());
				break; // Damage only one enemy per key press
			}
		}
	}
}


void APRCharacterBase::OnHealthChanged(float CurrentHealth, float MaxHealth)
{
	Super::OnHealthChanged(CurrentHealth, MaxHealth); // Call parent implementation if it has any logic.

	// Player-specific logic here:
	UE_LOG(LogTemp, Log, TEXT("Player Health Changed: %.1f / %.1f"), CurrentHealth, MaxHealth);
}

void APRCharacterBase::OnDeath()
{
	Super::OnDeath(); // Call parent implementation to disable collision/movement.

	// Player-specific logic here:
	// For example, disable input and show a "Game Over" screen.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		DisableInput(PC);
	}
	UE_LOG(LogTemp, Warning, TEXT("PLAYER HAS DIED. GAME OVER."));
}