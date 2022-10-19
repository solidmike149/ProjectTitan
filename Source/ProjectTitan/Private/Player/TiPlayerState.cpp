// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/TiPlayerState.h"

#include "SaveSystem/TiSaveGame.h"

void ATiPlayerState::SavePlayerState_Implementation(UTiSaveGame* SaveObject)
{
	if (SaveObject)
	{
		// Gather all relevant data for player
		FPlayerSaveData SaveData;

		// May not be alive while we save
		if (APawn* MyPawn = GetPawn())
		{
			SaveData.Location = MyPawn->GetActorLocation();
			SaveData.Rotation = MyPawn->GetActorRotation();
			SaveData.bResumeAtTransform = true;
		}
		
		SaveObject->SavedPlayer = SaveData;
	}
}

void ATiPlayerState::LoadPlayerState_Implementation(UTiSaveGame* SaveObject)
{
	
}
