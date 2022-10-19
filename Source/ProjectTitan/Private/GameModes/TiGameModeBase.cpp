// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/TiGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "SaveSystem/TiSaveGameSubsystem.h"

void ATiGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	UTiSaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<UTiSaveGameSubsystem>();

	// Optional slot name (Falls back to slot specified in SaveGameSettings class/INI otherwise)
	FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
	
	SG->LoadSaveGame(SelectedSaveSlot);
}

void ATiGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{

	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	UTiSaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<UTiSaveGameSubsystem>();

	SG->LoadPawnData(NewPlayer);
	
	SG->OverrideSpawnTransform(NewPlayer);
}
