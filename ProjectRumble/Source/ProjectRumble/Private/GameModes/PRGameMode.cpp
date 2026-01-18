// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PRGameMode.h"
#include "Player/PRPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PRStatsComponent.h"
#include "Game/PRGameState.h"
#include "AI/PRAIBase.h"
#include "Characters/PRCharacterBase.h"
#include "Managers/PRSpawnerManager.h"
#include "Player/PRPlayerController.h"

APRGameMode::APRGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.0f; // We dont need to tick every frame.
}

void APRGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RecalculateActiveDifficulty();
}

void APRGameMode::RegisterPlayerInMenu()
{
	// Increment the counter.
	PlayersInLevelUpMenu++;

	// Ensure the game is paused.
	if (!UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	UE_LOG(LogTemp, Log, TEXT("[GameMode] Player entered menu. Pending: %d"), PlayersInLevelUpMenu);
}

void APRGameMode::UnregisterPlayerInMenu()
{
	// Decrement the counter.
	PlayersInLevelUpMenu--;

	// Safety check
	if (PlayersInLevelUpMenu < 0) PlayersInLevelUpMenu = 0;

	UE_LOG(LogTemp, Log, TEXT("[GameMode] Player left menu. Pending: %d"), PlayersInLevelUpMenu);

	// If no one is left in the menu, unpause the game.
	if (PlayersInLevelUpMenu == 0)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		UE_LOG(LogTemp, Log, TEXT("[GameMode] All players ready. Game Unpaused."));
	}
}

void APRGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	// If a player leaves, force a check or decrement to prevent stuck pause state.
	// For a simple prototype, we can just force unpause or reset the counter if needed.
	// But ideally, we would check if 'Exiting' was one of the pending players.
}

void APRGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APRGameMode::StartPlay()
{
	Super::StartPlay();

	if (SpawnerManagerClass)
	{
		GetWorld()->SpawnActor<APRSpawnerManager>(SpawnerManagerClass);
		UE_LOG(LogTemp, Log, TEXT("Spawner Manager has been initialized by GameMode."));
	}
	//After spawning, start timer.
	if (APRGameState* GS = GetGameState<APRGameState>())
	{
		// Set the match duration from config.
		GS->SetMatchDuration(MatchDurationInSeconds);
	}
	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &APRGameMode::StartGameDelayed, 1.0f, false);
}

void APRGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// This is the SAFEST place to handle new player setup.
	if (NewPlayer)
	{
		if (APRPlayerState* PR_PlayerState = NewPlayer->GetPlayerState<APRPlayerState>())
		{
			// The PlayerState is guaranteed to exist here.
			// Now we wait for its internal components to be ready.
			PR_PlayerState->OnStatsComponentReady.AddDynamic(this, &APRGameMode::HandlePlayerReady);
		}

		if (NewPlayer->GetPawn() == nullptr)
		{
			RestartPlayer(NewPlayer); 
			UE_LOG(LogTemp, Warning, TEXT("[SERVER] Late joiner %s forced to spawn."), *NewPlayer->GetName());
		}

	}
}

void APRGameMode::StartGameDelayed()
{
	if (APRGameState* GS = GetGameState<APRGameState>())
	{
		GS->StartGameTimer();
		UE_LOG(LogTemp, Warning, TEXT("Game Mode: Match Started after delay."));
	}
}

void APRGameMode::CheckPlayerDeaths()
{
	// Iterate through all player controllers to check their status
	bool bIsAnyPlayerAlive = false;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Iterator->Get();
		if (PC && PC->GetPawn())
		{
			// If we have a Pawn, check its health via StatsComponent
			if (APRCharacterBase* Character = Cast<APRCharacterBase>(PC->GetPawn()))
			{
				if (UPRStatsComponent* Stats = Character->GetStatsComponent())
				{
					float CurrentHealth = Stats->GetStatValue(NativeGameplayTags::Stats::Defense::TAG_Stat_Defense_Health);
					if (CurrentHealth > 0.0f)
					{
						bIsAnyPlayerAlive = true;
						break; // Found a survivor, game continues
					}
				}
			}
		}
	}

	// If no one is alive, trigger Game Over
	if (!bIsAnyPlayerAlive)
	{
		GameOver(false); // false = Lost
	}
}

void APRGameMode::GameOver(bool bWon)
{
	UE_LOG(LogTemp, Warning, TEXT("GAME OVER! Won: %s"), bWon ? TEXT("Yes") : TEXT("No"));

	// Notify all players
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (APRPlayerController* PC = Cast<APRPlayerController>(Iterator->Get()))
		{
			PC->Client_ShowGameOverScreen(bWon);
		}
	}

	// Slow motion effect. But is this affecting menus? And even networked players?
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.25f);
}

void APRGameMode::HandlePlayerReady(UPRStatsComponent* PlayerStatsComp)
{
	if (PlayerStatsComp)
	{
		// 1. Bind to the difficulty change delegate.
		PlayerStatsComp->OnDifficultyChangedDelegate.AddDynamic(this, &APRGameMode::OnPlayerDifficultyChanged);

		// 2. A player is now fully ready, so we recalculate the game's difficulty.
		RecalculateActiveDifficulty();
	}
}

void APRGameMode::OnPlayerDifficultyChanged(float NewDifficultyValue)
{
	// A stat has changed on one player, so we must find the highest difficulty among ALL players.
	RecalculateActiveDifficulty();
}

void APRGameMode::RecalculateActiveDifficulty()
{
	// --- GUARD CLAUSE: Ensure GameState is valid before proceeding ---
	APRGameState* GS = GetGameState<APRGameState>();
	if (!GS) return;

	float HighestDifficulty = 1.0f;
	
	// --- 1. CALCULATE THE NEW DIFFICULTY MULTIPLIER ---
	for (APlayerState* PS : GS->PlayerArray)
	{
		if (APRPlayerState* PR_PS = Cast<APRPlayerState>(PS))
		{
			if (PR_PS->StatsComponent)
			{
				float PlayerDifficulty = PR_PS->StatsComponent->GetStatValue(NativeGameplayTags::Stats::Utility::TAG_Stat_Utiliy_Difficulty);
				HighestDifficulty = FMath::Max(HighestDifficulty, PlayerDifficulty);
			}
		}
	}

	float TimeBonus = 0.0f;
	float ServerTime = GS->GetServerGameTime();

	const float EndlessStartTime = GS->GetMatchDuration();

	// Endless 
	if (ServerTime > EndlessStartTime)
	{
		// Calculate how many minutes have passed since the endless mode started.
		float MinutesOver = (ServerTime - EndlessStartTime) / 60.0f;

		// Change per minute bonus as needed.
		TimeBonus = MinutesOver * ActiveDifficultyMultiplier;
	}

	float FinalMultiplier = HighestDifficulty + TimeBonus;

	// Apply the hard cap defined in the GameMode's properties.
	FinalMultiplier = FMath::Min(HighestDifficulty, MaxDifficultyMultiplier);

	// --- 2. UPDATE THE GAME STATE ---
	// Only proceed if the value has actually changed.
	if (!FMath::IsNearlyEqual(GS->GetActiveDifficultyMultiplier(), FinalMultiplier))
	{
		// Set the value on the GameState. The GameState will handle replicating this to clients.
		GS->SetActiveDifficultyMultiplier(FinalMultiplier);

		// Update all existing AI actors in the world with the new multiplier.
		TArray<AActor*> FoundAIs;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APRAIBase::StaticClass(), FoundAIs);

		for (AActor* AIActor : FoundAIs)
		{
			if (APRAIBase* AI = Cast<APRAIBase>(AIActor))
			{
				// Call the function on each AI to re-initialize its stats with the new multiplier.
				AI->UpdateDifficultyMultiplier(FinalMultiplier);
			}
		}
		// Log the change for debugging.
		UE_LOG(LogTemp, Log, TEXT("Active Difficulty Multiplier updated to: %.2f"), FinalMultiplier);
	}
	
}




