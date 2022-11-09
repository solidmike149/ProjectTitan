// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "DialogData.generated.h"


USTRUCT(BlueprintType)
struct FTiDialogLine : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Talker;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Line;
};

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UDialogData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TMap<FString, UTexture2D*> Portraits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lines")
	UDataTable* DialogLines;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Dialogs", GetFName());
	}
};
