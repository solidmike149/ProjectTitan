// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GiltSaveGameSubsystem.generated.h"

class UGiltSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGiltSaveGameSignature, class UGiltSaveGame*, SaveObject);

/**
 * Handles all saving/loading of game state and player data including transform
 */
UCLASS(meta=(DisplayName="SaveGame System"))
class PROJECTTITAN_API UGiltSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:

	/* Name of slot to save/load to disk. Filled by SaveGameSettings */
	FString CurrentSlotName;

	UPROPERTY()
	UGiltSaveGame* CurrentSaveGame;

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
	FGiltSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
	FGiltSaveGameSignature OnSaveGameWritten;
	
	void Initialize(FSubsystemCollectionBase& Collection) override;
};
