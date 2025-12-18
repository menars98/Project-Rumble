// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/PRSpawnerManager.h"
#include "AI/PRAIBase.h"
#include "GameModes/PRGameMode.h" 
#include "Kismet/GameplayStatics.h"
#include <Game/PRGameState.h>
#include "Datas/Wave/PRSpawnConfig.h" 
#include "PRGameplayTags.h"
#include "Curves/CurveFloat.h"


APRSpawnerManager::APRSpawnerManager()
{
	PrimaryActorTick.bCanEverTick = true; // We need tick to check the game time
	// This actor shouldnt live on client
	bReplicates = false;
}

void APRSpawnerManager::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		SetActorTickEnabled(false);
		return;
	}

    // 1. Take config from GameMode
	if (APRGameMode* GM = Cast<APRGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (UPRSpawnConfig* ConfigFromGM = GM->GetLevelSpawnConfig())
		{
			SpawnConfig = ConfigFromGM;
			UE_LOG(LogTemp, Log, TEXT("SpawnerManager: Config loaded from GameMode: %s"), *SpawnConfig->GetName());
		}
	}

	if (!SpawnConfig)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnerManager: No Config found in GameMode! Checking local fallback..."));
	}

	if (!SpawnConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnerManager: CRITICAL ERROR - No SpawnConfig assigned!"));
		SetActorTickEnabled(false);
		return;
	}

	// 3. Deck Oluþtur
	BuildRunDeck();

	// 2. Start Spawning
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APRSpawnerManager::SpawnLoop, SpawnCheckInterval, true);
	
}

void APRSpawnerManager::BuildRunDeck()
{
	if (!SpawnConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnerManager has no Config assigned!"));
		return;
	}

	CurrentRunDeck.Empty();

	// --- 1. FILTER CATALOG (Biome Check) ---
	// Group all valid candidates by their Tier.
	TMap<FGameplayTag, TArray<TSubclassOf<APRAIBase>>> CandidatesByTier;

	for (const FEnemyCatalogEntry& Entry : SpawnConfig->EnemyCatalog)
	{
		if (!Entry.AIClass) continue;

		// --- 1. POPULATE SPECIFIC CACHE (O(1) Access) ---
	    // We assume the AI Class has an identifying tag in its "AITags" or we use a tag from the Catalog entry.
	    // For this to work, FEnemyCatalogEntry needs a "TypeTag" property, OR 
	    // we assume the user adds the "Enemy.Type.X" tag to the AI's CDO (Class Default Object).

	    // Let's assume we added a "TypeTag" to FEnemyCatalogEntry in SpawnConfig.h for simplicity,
	    // OR we can read it from the Blueprint Default Properties.
	    // Let's grab tags from the CDO (Class Default Object) to be safe and dynamic.
		if (const APRAIBase* CDO = Cast<APRAIBase>(Entry.AIClass->GetDefaultObject()))
		{
			// The AI should have a tag like "Enemy.Type.Goblin" in its AITags container.
			for (const FGameplayTag& Tag : CDO->GetAITags())
			{
				if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag("Enemies.Type")))
				{
					SpecificEnemyCache.Add(Tag, Entry.AIClass);
				}
			}
		}

		// --- 2. BIOME FILTER FOR RUN DECK ---
		bool bBiomeMatch = Entry.BiomeTags.HasTag(NativeGameplayTags::Enemies::Biome::TAG_Enemies_Biome_Global) ||
			Entry.BiomeTags.HasTag(SpawnConfig->LevelBiomeTag);

		if (bBiomeMatch)
		{
			CandidatesByTier.FindOrAdd(Entry.TierTag).Add(Entry.AIClass);
		}
	}

	// --- 3. DRAFT THE DECK (Selection) ---
	// For each Tier, pick 'N' random enemies as defined in config.
	for (const auto& Pair : SpawnConfig->RunDeckSelectionCounts)
	{
		FGameplayTag Tier = Pair.Key;
		int32 NumToSelect = Pair.Value;

		if (TArray<TSubclassOf<APRAIBase>>* Candidates = CandidatesByTier.Find(Tier))
		{
			// Shuffle the candidates to pick random ones
			int32 LastIndex = Candidates->Num() - 1;
			for (int32 i = 0; i <= LastIndex; ++i)
			{
				int32 Index = FMath::RandRange(i, LastIndex);
				if (i != Index) Candidates->Swap(i, Index);
			}

			// Take the first N items (or all if N is larger than available)
			int32 Count = FMath::Min(NumToSelect, Candidates->Num());
			for (int32 i = 0; i < Count; ++i)
			{
				CurrentRunDeck.FindOrAdd(Tier).Add((*Candidates)[i]);
				UE_LOG(LogTemp, Log, TEXT("Deck Draft: Added %s to %s"), *((*Candidates)[i]->GetName()), *Tier.ToString());
			}
		}
	}
}

void APRSpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority() || !SpawnConfig) return;

	float GameTime = 0.f;
	float DifficultyMultiplier = 1.0f;

	if (APRGameState* GS = GetWorld()->GetGameState<APRGameState>())
	{
		GameTime = GS->GetServerGameTime();
		DifficultyMultiplier = GS->GetActiveDifficultyMultiplier();
	}

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player)
	{
		CheckBossEvents(GameTime, Player);
	}

	// --- 1. CALCULATE TARGET COUNT (FROM CURVE) ---
	float BaseTarget = 0.f;
	if (SpawnConfig->SpawnCapCurve)
	{
		// Read directly from the curve
		BaseTarget = SpawnConfig->SpawnCapCurve->GetFloatValue(GameTime);
	}

	// Apply Difficulty Multiplier
	int32 CalculatedTarget = FMath::RoundToInt(BaseTarget * DifficultyMultiplier);

	// Apply Hard Cap
	TargetAICount = FMath::Min(CalculatedTarget, AbsoluteMaxAI);
	CurrentMaxActiveAI = TargetAICount; // In this system, Target IS the Cap.
}

TSubclassOf<APRAIBase> APRSpawnerManager::GetEnemyToSpawn(float GameTime)
{
	if (!SpawnConfig || SpawnConfig->Timeline.Num() == 0) return nullptr;

	// 1. Find Current Segment
	const FSpawnSegment* ActiveSegment = nullptr;
	// Iterate backwards to find latest valid segment (Handles Endless if last segment is kept)
	for (int32 i = SpawnConfig->Timeline.Num() - 1; i >= 0; --i)
	{
		if (GameTime >= SpawnConfig->Timeline[i].StartTime)
		{
			ActiveSegment = &SpawnConfig->Timeline[i];
			break;
		}
	}

	if (!ActiveSegment) return nullptr;

	// 2. Weighted Random Selection for TAG (Tier OR Specific)
	float TotalWeight = 0.f;
	for (const auto& Pair : ActiveSegment->SpawnWeights)
	{
		TotalWeight += Pair.Value;
	}

	if (TotalWeight <= 0.f) return nullptr;

	float RandomRoll = FMath::FRandRange(0.f, TotalWeight);
	float CurrentWeight = 0.f;
	FGameplayTag SelectedTag = FGameplayTag::EmptyTag;

	for (const auto& Pair : ActiveSegment->SpawnWeights)
	{
		CurrentWeight += Pair.Value;
		if (RandomRoll <= CurrentWeight)
		{
			SelectedTag = Pair.Key;
			break;
		}
	}

	// 3. Resolve the Tag into a Class
	return ResolveSpawnTag(SelectedTag);
}

TSubclassOf<APRAIBase> APRSpawnerManager::ResolveSpawnTag(FGameplayTag Tag)
{
	if (!Tag.IsValid()) return nullptr;

	// CASE A: It is a TIER Tag (e.g., "Enemies.Tier.1")
	// Check if we have a deck for this tier.
	if (TArray<TSubclassOf<APRAIBase>>* Deck = CurrentRunDeck.Find(Tag))
	{
		if (Deck->Num() > 0)
		{
			int32 RandIndex = FMath::RandRange(0, Deck->Num() - 1);
			return (*Deck)[RandIndex];
		}
	}

	// CASE B: It is a SPECIFIC TYPE Tag (e.g., "Enemies.Type.Goblin")
	// Check our cache.
	if (TSubclassOf<APRAIBase>* SpecificClass = SpecificEnemyCache.Find(Tag))
	{
		return *SpecificClass;
	}

	// Fallback: If tag found nowhere (maybe logic error in config)
	UE_LOG(LogTemp, Warning, TEXT("Spawn Manager: Could not resolve spawn tag %s"), *Tag.ToString());
	return nullptr;
}

void APRSpawnerManager::CheckBossEvents(float GameTime, ACharacter* Player)
{
	if (!SpawnConfig) return;

	// Have we reached the end of the list ?
	if (!SpawnConfig->BossEvents.IsValidIndex(NextBossEventIndex)) return;

	const FBossSpawnEvent& NextEvent = SpawnConfig->BossEvents[NextBossEventIndex];

	if (GameTime >= NextEvent.TriggerTime)
	{
		// --- SPAWN BOSS ---
		if (NextEvent.BossClass)
		{
			FVector Loc = FindSafeSpawnLocation(Player->GetActorLocation(), SpawnRadius);

			// Bosses generally spawn a bit further away; we can increase the radius
			// Loc = FindSafeSpawnLocation(Player->GetActorLocation(), SpawnRadius * 1.5f);
			APRAIBase* Boss = GetWorld()->SpawnActorDeferred<APRAIBase>(
				NextEvent.BossClass,
				FTransform(FRotator::ZeroRotator, Loc),
				nullptr, nullptr,
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
			);

			if (Boss)
			{
				// If there is a special setup for the boss (HP bar, etc.), we can do it here.
				// Boss->SetAsBoss(); 
				UGameplayStatics::FinishSpawningActor(Boss, FTransform(FRotator::ZeroRotator, Loc));

				UE_LOG(LogTemp, Warning, TEXT("BOSS SPAWNED: %s"), *Boss->GetName());

				// UI Message (Optional)
				// if (!NextEvent.WarningMessage.IsEmpty()) { ... }
			}
		}
		// Proceed to the next boss
		NextBossEventIndex++;
	}
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
	// Check current count
	TArray<AActor*> FoundAIs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRAIBase::StaticClass(), FoundAIs);

	int32 Gap = TargetAICount - FoundAIs.Num();
	int32 MaxPerTick = 5;
	int32 NumToSpawn = FMath::Clamp(Gap, 0, MaxPerTick);

	if (NumToSpawn <= 0) return;

	float GameTime = 0.f;
	if (APRGameState* GS = GetWorld()->GetGameState<APRGameState>())
	{
		GameTime = GS->GetServerGameTime();
	}

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!Player) return;

	for (int32 i = 0; i < NumToSpawn; ++i)
	{
		TSubclassOf<APRAIBase> ClassToSpawn = GetEnemyToSpawn(GameTime);
		if (!ClassToSpawn) continue;

		FVector Loc = FindSafeSpawnLocation(Player->GetActorLocation(), SpawnRadius);

		APRAIBase* NewEnemy = GetWorld()->SpawnActorDeferred<APRAIBase>(
			ClassToSpawn,
			FTransform(FRotator::ZeroRotator, Loc),
			nullptr, nullptr,
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
		);

		if (NewEnemy)
		{
			UGameplayStatics::FinishSpawningActor(NewEnemy, FTransform(FRotator::ZeroRotator, Loc));
		}
	}
}

