// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GiltSaveGameSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Save Game Settings"))
class PROJECTTITAN_API UGiltSaveGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UGiltSaveGameSettings();
	
	/* Default slot name if UI doesn't specify any */ 
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString SaveSlotName;
};
