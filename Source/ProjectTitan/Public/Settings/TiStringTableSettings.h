// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TiStringTableSettings.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="StringTable Settings"))
class PROJECTTITAN_API UTiStringTableSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FName DiaryTablePath;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FName DialogTablePath;

	UTiStringTableSettings();
};
