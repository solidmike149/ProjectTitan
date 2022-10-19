// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TiSaveGame.generated.h"

USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()
	
	/* Identifier for which Actor this belongs to */
	UPROPERTY()
	FName ActorName;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
	TArray<uint8> ByteData;
};

USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	bool bResumeAtTransform;

	/* Contains all 'SaveGame' marked variables of the Actor */
	UPROPERTY()
	TArray<uint8> ByteData;
};


/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FActorSaveData> SavedActors;

	UPROPERTY()
	FPlayerSaveData SavedPlayer;
};
