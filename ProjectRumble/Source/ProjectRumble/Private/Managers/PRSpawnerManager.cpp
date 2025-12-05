// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRSpawnerManager.h"
#include "AI/PRAIBase.h"
#include "GameModes/PRGameMode.h" 
#include "Kismet/GameplayStatics.h"
#include <Game/PRGameState.h>
#include "Datas/Wave/PRSpawnConfig.h" 


APRSpawnerManager::APRSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = true; // We need tick to check the game time
	// This actor shouldnt live on client
	bReplicates = false;
	NextWaveIndex = 0;
	TargetAICount = 0;
	NextBossIndex = 0;
}

void APRSpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		// If this is a client, disable ticking to save performance and prevent logic execution.
		SetActorTickEnabled(false);

		// Clear any timers if they were somehow set (precautionary).
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);

		UE_LOG(LogTemp, Log, TEXT("[CLIENT] APRSpawnerManager disabled on client."));
		return;
	}
	CurrentMaxActiveAI = BaseMaxActiveAI;

	// Start the spawn loop timer
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APRSpawnerManager::SpawnLoop, SpawnCheckInterval, true, 1.0f);
	
}

// Called every frame
void APRSpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Double check authority (though SetActorTickEnabled(false) in BeginPlay should handle it).
	if (!HasAuthority())
	{
		return;
	}

	// Don't use GetTimeSeconds(). Use the synchronized game time from GameState.
	float GameTime = 0.f;

	// --- GET DIFFICULTY MULTIPLIER ---
	float DifficultyMultiplier = 1.0f;
	if (APRGameState* PRGameState = GetWorld()->GetGameState<APRGameState>())
	{
		// Get the synced time that respects pause/gameplay flow.
		GameTime = PRGameState->GetServerGameTime();

		// Get the difficulty multiplier while we are here.
		DifficultyMultiplier = PRGameState->GetActiveDifficultyMultiplier();
	}

	ProcessWaveTimeline(GameTime, DifficultyMultiplier);
	ProcessBossTimeline(GameTime);
	// --- OUR DYNAMIC MAX AI LOGIC (Endless Mode Prep) ---

	// For now, let's assume Endless Mode starts after a fixed duration (e.g., 10 minutes).
	// The GameMode is a better place to define this length.
	const float EndlessModeStartTime = 600.0f; // 10 minutes (600 seconds)

	bool bInEndlessMode = (GameTime >= EndlessModeStartTime);

	// The max number of active AI is also scaled by difficulty.
	int32 ScaledBaseMaxAI = FMath::RoundToInt(BaseMaxActiveAI * DifficultyMultiplier);

	if (bInEndlessMode)
	{
		// Calculate time passed since the beginning of Endless Mode.
		float EndlessTime = GameTime - EndlessModeStartTime;
		int32 MinutesPassed = FMath::FloorToInt(EndlessTime / 60.f);

		// Increase the max AI limit.
		CurrentMaxActiveAI = ScaledBaseMaxAI + (MinutesPassed * MaxAIIncreasePerMinute_Endless);

		// @TODO: Add logic to spawn Endless AI types here.
	}
	else
	{
		// Maintain the base limit during the initial 10 minutes.
		CurrentMaxActiveAI = ScaledBaseMaxAI;
	}

}

void APRSpawnerManager::ProcessWaveTimeline(float GameTime, float DifficultyMultiplier)
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// Check if there are any waves left to process
	if (!SpawnConfig->Waves.IsValidIndex(NextWaveIndex))
	{
		return; // All scheduled waves are done
	}

	// Check if it's time for the next wave
	if (GameTime >= SpawnConfig->Waves[NextWaveIndex].TimeToStart)
	{
		// Scale the population increase by the difficulty multiplier.
		int32 ScaledPopulationIncrease = FMath::RoundToInt(SpawnConfig->Waves[NextWaveIndex].PopulationIncrease * DifficultyMultiplier);

		// It's time! Increase the target population
		TargetAICount += ScaledPopulationIncrease;
		UE_LOG(LogTemp, Log, TEXT("Wave %d triggered! Target AI count is now %d (Scaled by %.2fx)"), NextWaveIndex, TargetAICount, DifficultyMultiplier);

		// Move to the next wave in the timeline
		NextWaveIndex++;
	}
}

void APRSpawnerManager::ProcessBossTimeline(float GameTime)
{
	// Check if all bosses are spawned or if we don't have a valid boss to check.
	if (!SpawnConfig->Bosses.IsValidIndex(NextBossIndex))
	{
		return;
	}

	const FBossWaveData& NextBoss = SpawnConfig->Bosses[NextBossIndex];

	// Check if it's time for the next boss to spawn.
	if (GameTime >= NextBoss.TimeToSpawn)
	{
		// 1. Spawn the Boss
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (PlayerCharacter && NextBoss.BossAIClass)
		{
			FVector SpawnLocation = FindSafeSpawnLocation(PlayerCharacter->GetActorLocation(), SpawnRadius);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			GetWorld()->SpawnActor<APRAIBase>(NextBoss.BossAIClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

			// @TODO: Start Boss Music
		}

		NextBossIndex++;
	}
}

TSubclassOf<APRAIBase> APRSpawnerManager::GetWeightedRandomActiveAIClass(float GameTime) const
{
	TArray<FSpawnWeight> CurrentSpawnWeights;
	float TotalWeight = 0.0f;

	// Only iterate through waves that have already started.
	for (int32 i = 0; i < NextWaveIndex; ++i)
	{
		const FWaveData& Wave = SpawnConfig->Waves[i];
		if (!Wave.AIClass) continue;

		// 1. Calculate the time this wave has been active, in minutes.
		float TimeActive = GameTime - Wave.TimeToStart;
		int32 MinutesActive = FMath::FloorToInt(TimeActive / 60.f);

		// 2. Calculate the decay: Initial % - (Time Active * Decay Rate)
		float CurrentPercentage = Wave.InitialSpawnPercentage - (MinutesActive * Wave.PercentageDecayPerMinute);

		// 3. Apply the Minimum Spawn Percentage (The core fix)
		// The weight is either the calculated percentage or the defined minimum, whichever is higher.
		CurrentPercentage = FMath::Max(Wave.MinimumSpawnPercentage, CurrentPercentage);

		// Only add to the pool if the weight is positive.
		if (CurrentPercentage > 0.0f)
		{
			CurrentSpawnWeights.Add({ Wave.AIClass, CurrentPercentage });
			TotalWeight += CurrentPercentage;
		}
	}

	// 4. Perform Weighted Random Selection
	if (TotalWeight <= 0.0f) return nullptr;

	float RandomValue = FMath::FRandRange(0.0f, TotalWeight);
	float CurrentWeightSum = 0.0f;

	for (const FSpawnWeight& SpawnWeight : CurrentSpawnWeights)
	{
		CurrentWeightSum += SpawnWeight.Weight;
		if (RandomValue <= CurrentWeightSum)
		{
			return SpawnWeight.AIClass; // Found the winning AI type.
		}
	}

	// Fallback in case of floating point errors, return a random one (should not happen if TotalWeight > 0).
	return CurrentSpawnWeights[FMath::RandRange(0, CurrentSpawnWeights.Num() - 1)].AIClass;
}

FVector APRSpawnerManager::FindSafeSpawnLocation(const FVector& CenterLocation, float Radius) const
{
	// 1. Calculate a random point on the XY plane around the center.
	// FMath::VRand() returns a random unit vector (not safe for 2D). 
	// FMath::VRand().GetSafeNormal2D() returns a random unit vector on the XY plane.
	FVector RandomDirection = FMath::VRand().GetSafeNormal2D();
	FVector GroundXY = CenterLocation + (RandomDirection * Radius);

	// 2. Setup the Line Trace (from high up to below the ground)
	FVector StartTrace = GroundXY;
	// We start the trace 1000 units above the ground to ensure we hit the terrain.
	StartTrace.Z += 1000.f;

	FVector EndTrace = GroundXY;
	// We trace down to 1000 units below the ground.
	EndTrace.Z -= 1000.f;

	FHitResult HitResult;

	// Set the trace parameters. 
	FCollisionQueryParams Params;
	// Ignore the Spawner Manager itself and the player (Owner).
	Params.AddIgnoredActor(this);
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		Params.AddIgnoredActor(Player);
	}

	// 3. Perform the Trace
	// We use Visibility channel to hit the static ground/landscape mesh.
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartTrace,
		EndTrace,
		ECollisionChannel::ECC_Visibility, // The channel used to hit the ground.
		Params
	);

	// 4. Return the snapped location
	if (bHit)
	{
		// Add a small Z offset to ensure the spawned actor is NOT clipping the ground.
		// A Character/Pawn is usually half its height above the hit point.
		const float SpawnAboveGroundOffset = 90.0f; // Typical half-height of a humanoid character

		FVector SafeLocation = HitResult.Location;
		SafeLocation.Z += SpawnAboveGroundOffset;

		return SafeLocation;
	}

	// Fallback: If no ground was found, return the initial XY position with a default Z.
	return GroundXY + FVector(0.f, 0.f, 100.0f);
}

void APRSpawnerManager::SpawnLoop()
{
	// 1. DETERMINE CURRENT AI COUNT (Slow but standard prototype method)
	TArray<AActor*> FoundAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRAIBase::StaticClass(), FoundAIs);
	int32 ActiveAICount = FoundAIs.Num();

	// 2. CALCULATE NUMBER TO SPAWN
	int32 NumToSpawn = TargetAICount - ActiveAICount;

	// Clamp NumToSpawn so it doesn't exceed the CurrentMaxActiveAI limit.
	NumToSpawn = FMath::Min(NumToSpawn, CurrentMaxActiveAI - ActiveAICount);

	if (NumToSpawn <= 0)
	{
		return; // No need to spawn
	}

	// 3. GET WEIGHTED AI CLASS
	float GameTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	TSubclassOf<APRAIBase> AIToSpawn = GetWeightedRandomActiveAIClass(GameTime);

	if (!AIToSpawn)
	{
		// Log error if no AI class could be selected (e.g., if TotalWeight is 0).
		UE_LOG(LogTemp, Warning, TEXT("SpawnLoop failed to select a weighted AI class."));
		return;
	}

	// 4. FIND PLAYER AND SPAWN
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return; // Cannot spawn without a player reference.
	}

	FVector PlayerLocation = PlayerCharacter->GetActorLocation();

	for (int32 i = 0; i < NumToSpawn; ++i)
	{
		FVector SpawnLocation = FindSafeSpawnLocation(PlayerCharacter->GetActorLocation(), SpawnRadius);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// @TODO: Add "camera check" (not too close to the screen) and "ground check" logic here.

		// Spawn the selected AI class
		GetWorld()->SpawnActor<APRAIBase>(AIToSpawn, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}