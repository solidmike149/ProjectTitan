// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TiSaveGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, class UTiSaveGame*, SaveObject);

/**
 * Handles all saving/loading of game state and player data including transform
 */
UCLASS(meta=(DisplayName="SaveGame System"))
class PROJECTTITAN_API UTiSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/* Name of slot to save/load to disk. Filled by SaveGameSettings */
	FString CurrentSlotName;

	UPROPERTY()
	UTiSaveGame* CurrentSaveGame;

public:

	/* Restore serialized data from PlayerState into player */
	void HandleStartingNewPlayer(AController* NewPlayer);

	void LoadPawnData(AController* Player);

	/* Restore spawn transform using stored data per PlayerState after being fully initialized. */
	UFUNCTION(BlueprintCallable)
	bool OverrideSpawnTransform(AController* Player);

	/* Change slot name, will be used next time we load/save data */
	UFUNCTION(BlueprintCallable)
	void SetSlotName(FString NewSlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame(bool bShouldSavePlayerTransform);

	void SavePlayerData(bool bSaveTransform);

	/* Load from disk, optional slot name */
	void LoadSaveGame(FString InSlotName = "");

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameWritten;
	
	void Initialize(FSubsystemCollectionBase& Collection) override;
};
