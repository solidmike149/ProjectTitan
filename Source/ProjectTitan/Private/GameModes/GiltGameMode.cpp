// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GiltGameMode.h"

#include "GiltLogChannels.h"
#include "TimerManager.h"
#include "Characters/GiltCharacter.h"
#include "Development/GiltDeveloperSettings.h"
#include "Engine/World.h"
#include "GameModes/GiltExperienceDefinition.h"
#include "GameModes/GiltExperienceManagerComponent.h"
#include "GameModes/GiltGameState.h"
#include "GameModes/GiltWorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Player/GiltPlayerController.h"
#include "Player/GiltPlayerState.h"
#include "SaveSystem/GiltSaveGameSubsystem.h"
#include "System/GiltAssetManager.h"
#include "UI/GiltHUD.h"

AGiltGameMode::AGiltGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AGiltGameState::StaticClass();
	PlayerControllerClass = AGiltPlayerController::StaticClass();
	PlayerStateClass = AGiltPlayerState::StaticClass();
	DefaultPawnClass = AGiltCharacter::StaticClass();
	HUDClass = AGiltHUD::StaticClass();
}

void AGiltGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	UGiltSaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<UGiltSaveGameSubsystem>();

	// Optional slot name (Falls back to slot specified in SaveGameSettings class/INI otherwise)
	FString SelectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
	
	SG->LoadSaveGame(SelectedSaveSlot);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void AGiltGameMode::HandleMatchAssignmentIfNotExpectingOne()
{
	FPrimaryAssetId ExperienceId;
	FString ExperienceIdSource;

	// Precedence order (highest wins)
	//  - Matchmaking assignment (if present)
	//  - URL Options override
	//  - Developer Settings (PIE only)
	//  - Command Line override
	//  - World Settings
	//  - Default experience

	UWorld* World = GetWorld();

	if (!ExperienceId.IsValid() && UGameplayStatics::HasOption(OptionsString, TEXT("Experience")))
	{
		const FString ExperienceFromOptions = UGameplayStatics::ParseOption(OptionsString, TEXT("Experience"));
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType(UGiltExperienceDefinition::StaticClass()->GetFName()), FName(*ExperienceFromOptions));
		ExperienceIdSource = TEXT("OptionsString");
	}

	if (!ExperienceId.IsValid() && World->IsPlayInEditor())
	{
		ExperienceId = GetDefault<UGiltDeveloperSettings>()->ExperienceOverride;
		ExperienceIdSource = TEXT("DeveloperSettings");
	}

	// see if the command line wants to set the experience
	if (!ExperienceId.IsValid())
	{
		FString ExperienceFromCommandLine;
		if (FParse::Value(FCommandLine::Get(), TEXT("Experience="), ExperienceFromCommandLine))
		{
			ExperienceId = FPrimaryAssetId::ParseTypeAndName(ExperienceFromCommandLine);
			ExperienceIdSource = TEXT("CommandLine");
		}
	}

	// see if the world settings has a default experience
	if (!ExperienceId.IsValid())
	{
		if (AGiltWorldSettings* TypedWorldSettings = Cast<AGiltWorldSettings>(GetWorldSettings()))
		{
			ExperienceId = TypedWorldSettings->GetDefaultGameplayExperience();
			ExperienceIdSource = TEXT("WorldSettings");
		}
	}

	UGiltAssetManager& AssetManager = UGiltAssetManager::Get();
	FAssetData Dummy;
	if (ExperienceId.IsValid() && !AssetManager.GetPrimaryAssetData(ExperienceId, /*out*/ Dummy))
	{
		UE_LOG(LogGiltExperience, Error, TEXT("EXPERIENCE: Wanted to use %s but couldn't find it, falling back to the default)"), *ExperienceId.ToString());
		ExperienceId = FPrimaryAssetId();
	}

	// Final fallback to the default experience
	if (!ExperienceId.IsValid())
	{
		//@TODO: Pull this from a config setting or something
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("GIltExperienceDefinition"), FName("B_DefaultExperience"));
		ExperienceIdSource = TEXT("Default");
	}

	OnMatchAssignmentGiven(ExperienceId, ExperienceIdSource);
}

void AGiltGameMode::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId, const FString& ExperienceIdSource)
{
#if WITH_SERVER_CODE
	if (ExperienceId.IsValid())
	{
		UE_LOG(LogGiltExperience, Log, TEXT("Identified experience %s (Source: %s)"), *ExperienceId.ToString(), *ExperienceIdSource);

		UGiltExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGiltExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->ServerSetCurrentExperience(ExperienceId);
	}
	else
	{
		UE_LOG(LogGiltExperience, Error, TEXT("Failed to identify experience, loading screen will stay up forever"));
	}
#endif
}

void AGiltGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	UGiltSaveGameSubsystem* SG = GetGameInstance()->GetSubsystem<UGiltSaveGameSubsystem>();

	SG->LoadPawnData(NewPlayer);
	
	SG->OverrideSpawnTransform(NewPlayer);
}

bool AGiltGameMode::IsExperienceLoaded() const
{
	check(GameState);
	UGiltExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGiltExperienceManagerComponent>();
	check(ExperienceComponent);

	return ExperienceComponent->IsExperienceLoaded();
}

