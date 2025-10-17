// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRSpawnerManager.h"
#include "AI/PRAIBase.h"
#include "GameModes/PRGameMode.h" 
#include "Kismet/GameplayStatics.h"

APRSpawnerManager::APRSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = true; // We need tick to check the game time
	NextWaveIndex = 0;
	TargetAICount = 0;

}

// Called when the game starts or when spawned
void APRSpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentMaxActiveAI = BaseMaxActiveAI;

	// Start the spawn loop timer
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APRSpawnerManager::SpawnLoop, SpawnCheckInterval, true, 1.0f);
	
}

// Called every frame
void APRSpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessWaveTimeline();

	// --- OUR DYNAMIC MAX AI LOGIC ---
	// Get game state from GameMode (assuming we have a function for this)
	// Example:
	// if (GameMode->IsInEndlessMode())
	// {
	//     float EndlessTime = GameMode->GetTimeInEndlessMode();
	//     int32 MinutesPassed = FMath::FloorToInt(EndlessTime / 60.f);
	//     CurrentMaxActiveAI = BaseMaxActiveAI + (MinutesPassed * MaxAIIncreasePerMinute_Endless);
	// }

}

void APRSpawnerManager::ProcessWaveTimeline()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	// Check if there are any waves left to process
	if (!WaveTimeline.IsValidIndex(NextWaveIndex))
	{
		return; // All scheduled waves are done
	}

	// Get the current game time from the GameMode or GameState
	float GameTime = GetWorld()->GetAuthGameMode()->GetWorld()->GetTimeSeconds();

	// Check if it's time for the next wave
	if (GameTime >= WaveTimeline[NextWaveIndex].TimeToStart)
	{
		// It's time! Increase the target population
		TargetAICount += WaveTimeline[NextWaveIndex].PopulationIncrease;
		UE_LOG(LogTemp, Log, TEXT("Wave %d triggered! Target AI count is now %d"), NextWaveIndex, TargetAICount);

		// Move to the next wave in the timeline
		NextWaveIndex++;
	}
}

void APRSpawnerManager::SpawnLoop()
{
	// Get the current number of active AI. This is the most complex part.
	// We need a way to track this. A simple but slow way is to iterate all actors.
	// A better way is to have AIs register/unregister themselves with the spawner.

	// For now, let's use the simple (slow) method for the prototype:
	TArray<AActor*> FoundAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRAIBase::StaticClass(), FoundAIs);
	int32 ActiveAICount = FoundAIs.Num();

	// Check if we need to spawn more AI
	int32 NumToSpawn = TargetAICount - ActiveAICount;

	// Also, don't spawn more than the max allowed AI
	NumToSpawn = FMath::Min(NumToSpawn, CurrentMaxActiveAI - ActiveAICount);

	if (NumToSpawn <= 0)
	{
		return; // No need to spawn
	}

	// @TODO: Spawn 'NumToSpawn' enemies using the pooling system
	// This loop will be more complex, choosing which AI type to spawn based on the wave data.
	// For a simple start, let's just spawn the last wave's AI type.
	if (WaveTimeline.IsValidIndex(NextWaveIndex - 1))
	{
		const FWaveData& LastWave = WaveTimeline[NextWaveIndex - 1];
		if (LastWave.AIClass)
		{
			for (int32 i = 0; i < NumToSpawn; ++i)
			{
				// Find spawn location logic here...
				// We need a reference to the player first.
				ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
				if (PlayerCharacter)
				{
					// Get a random point within the SpawnRadius around the player
					FVector SpawnLocation = PlayerCharacter->GetActorLocation() + FMath::VRand().GetSafeNormal2D() * SpawnRadius;

					// TODO: Add "camera check" and "ground check" logic here.

					GetWorld()->SpawnActor<APRAIBase>(LastWave.AIClass, SpawnLocation, FRotator::ZeroRotator);
				}
			}
			UE_LOG(LogTemp, Log, TEXT("Spawner is spawning %d units."), NumToSpawn);
		}
	}
}