// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "GiltDeveloperSettings.generated.h"


UENUM()
enum class ECheatExecutionTime
{
	// When the cheat manager is created
	OnCheatManagerCreated,

	// When a pawn is possessed by a player
	OnPlayerPawnPossession
};

USTRUCT()
struct FGiltCheatToRun
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	ECheatExecutionTime Phase = ECheatExecutionTime::OnPlayerPawnPossession;

	UPROPERTY(EditAnywhere)
	FString Cheat;
};
/**
 * Developer settings / editor cheats
 */
UCLASS(config=EditorPerProjectUserSettings, MinimalAPI)
class UGiltDeveloperSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UGiltDeveloperSettings();

	//~UDeveloperSettings interface
	virtual FName GetCategoryName() const override;
	//~End of UDeveloperSettings interface
	
	// The experience override to use for Play in Editor (if not set, the default for the world settings of the open map will be used)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, config, Category=Gilt, meta=(AllowedTypes="GiltExperienceDefinition"))
	FPrimaryAssetId ExperienceOverride;

	// List of cheats to auto-run during 'play in editor'
	UPROPERTY(config, EditAnywhere, Category=Gilt)
	TArray<FGiltCheatToRun> CheatsToRun;

#if WITH_EDITOR
	
	// Called by the editor engine to let us pop reminder notifications when cheats are active
	PROJECTTITAN_API void OnPlayInEditorStarted() const;

#endif
};
