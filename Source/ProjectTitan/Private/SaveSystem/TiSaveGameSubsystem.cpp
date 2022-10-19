// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSystem/TiSaveGameSubsystem.h"

#include "EngineUtils.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TiPlayerState.h"
#include "SaveSystem/TiSaveGame.h"
#include "SaveSystem/TiSaveGameSettings.h"
#include "SaveSystem/TiSaveInterface.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UTiSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UTiSaveGameSettings* SGSettings = GetDefault<UTiSaveGameSettings>();
	// Access defaults from DefaultGame.ini
	CurrentSlotName = SGSettings->SaveSlotName;
}

void UTiSaveGameSubsystem::HandleStartingNewPlayer(AController* NewPlayer)
{
	ATiPlayerState* PS = NewPlayer->GetPlayerState<ATiPlayerState>();
	if (ensure(PS))
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}
}

void UTiSaveGameSubsystem::LoadPawnData(AController* Player)
{
	FMemoryReader MemReader(CurrentSaveGame->SavedPlayer.ByteData);

	FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
	Ar.ArIsSaveGame = true;

	APawn* Pawn = Player->GetPawn();
	// Convert binary array back into pawn's variables
	Pawn->Serialize(Ar);

	ITiSaveInterface::Execute_OnActorLoaded(Pawn);
	
}

bool UTiSaveGameSubsystem::OverrideSpawnTransform(AController* Player)
{
	if (!IsValid(Player))
	{
		return false;
	}

	APlayerState* PS = Player->GetPlayerState<APlayerState>();
	if (PS == nullptr)
	{
		return false;
	}
	
	if (APawn* MyPawn = PS->GetPawn())
	{
		FPlayerSaveData FoundData = CurrentSaveGame->SavedPlayer;
		if (FoundData.bResumeAtTransform)
		{		
			MyPawn->SetActorLocation(FoundData.Location);
			MyPawn->SetActorRotation(FoundData.Rotation);
			
			return true;
		}
	}

	return false;
}

void UTiSaveGameSubsystem::SetSlotName(FString NewSlotName)
{
	// Ignore empty name
	if (NewSlotName.Len() == 0)
	{
		return;
	}
	
	CurrentSlotName = NewSlotName;
}

void UTiSaveGameSubsystem::WriteSaveGame(bool bShouldSavePlayerTransform)
{
	CurrentSaveGame->SavedActors.Empty();

	SavePlayerData(bShouldSavePlayerTransform);

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		
		// Only interested in our 'gameplay actors', skip actors that are being destroyed
		if (!IsValid(Actor) || !Actor->Implements<UTiSaveInterface>())
		{
			continue;
		}

		FActorSaveData ActorData;
		ActorData.ActorName = Actor->GetFName();
		
		// Pass the array to fill with data from Actor
		FMemoryWriter MemWriter(ActorData.ByteData);

		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		// Find only variables with UPROPERTY(SaveGame)
		Ar.ArIsSaveGame = true;
		// Converts Actor's SaveGame UPROPERTIES into binary array
		Actor->Serialize(Ar);

		CurrentSaveGame->SavedActors.Add(ActorData);
	}

	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSlotName, 0);

	OnSaveGameWritten.Broadcast(CurrentSaveGame);
}

void UTiSaveGameSubsystem::SavePlayerData(bool bSaveTransform)
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FPlayerSaveData PlayerData;

	PlayerData.Location = Pawn->GetActorLocation();
	PlayerData.Rotation = Pawn->GetActorRotation();

	PlayerData.bResumeAtTransform = bSaveTransform;
		
	// Pass the array to fill with data from Actor
	FMemoryWriter MemWriter(PlayerData.ByteData);

	FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
	// Find only variables with UPROPERTY(SaveGame)
	Ar.ArIsSaveGame = true;
	// Converts Actor's SaveGame UPROPERTIES into binary array
	Pawn->Serialize(Ar);
}

void UTiSaveGameSubsystem::LoadSaveGame(FString InSlotName)
{
	// Update slot name first if specified, otherwise keeps default name
	SetSlotName(InSlotName);
	
	if (UGameplayStatics::DoesSaveGameExist(CurrentSlotName, 0))
	{
		CurrentSaveGame = Cast<UTiSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSlotName, 0));
		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Log, TEXT("Loaded SaveGame Data."));

		
		// Iterate the entire world of actors
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* Actor = *It;
			// Only interested in our 'gameplay actors'
			if (!Actor->Implements<UTiSaveInterface>())
			{
				continue;
			}

			for (FActorSaveData ActorData : CurrentSaveGame->SavedActors)
			{
				if (ActorData.ActorName == Actor->GetFName())
				{

					FMemoryReader MemReader(ActorData.ByteData);

					FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
					Ar.ArIsSaveGame = true;
					// Convert binary array back into actor's variables
					Actor->Serialize(Ar);

					ITiSaveInterface::Execute_OnActorLoaded(Actor);

					break;
				}
			}
		}

		OnSaveGameLoaded.Broadcast(CurrentSaveGame);
	}
	else
	{
		CurrentSaveGame = Cast<UTiSaveGame>(UGameplayStatics::CreateSaveGameObject(UTiSaveGame::StaticClass()));

		UE_LOG(LogTemp, Log, TEXT("Created New SaveGame Data."));
	}
}




