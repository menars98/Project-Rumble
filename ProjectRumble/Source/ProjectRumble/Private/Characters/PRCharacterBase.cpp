
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

void APRCharacterBase::BeginPlay()
{
	Super::BeginPlay(); 

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// --- SET CAMERA LIMITS FROM OUR EXPOSED VARIABLES ---
		if (PlayerController->PlayerCameraManager)
		{
			// Instead of hard-coded numbers, we now use the variables from our header file.
			// These can be changed in the BP_CharacterBase Blueprint.
			PlayerController->PlayerCameraManager->ViewPitchMin = CameraPitchMin;
			PlayerController->PlayerCameraManager->ViewPitchMax = CameraPitchMax;
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
	}

	// We will add Action bindings for Jump, Dash, Ability etc. here later.
}

void APRCharacterBase::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// MoveForward ve MoveRight mantýðýný bu tek vektörle birleþtir
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