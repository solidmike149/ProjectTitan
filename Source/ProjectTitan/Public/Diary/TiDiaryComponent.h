// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "UI/TiIndexData.h"
#include "TiDiaryComponent.generated.h"

USTRUCT(BlueprintType)
struct FDiaryEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString TitleKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CategoryKey;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FString> DescriptionKeys;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDiaryEntryAdded, UTiDiaryComponent*, Instigator, const FDiaryEntry&, DiaryEntry);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTITAN_API UTiDiaryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DiaryTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TMap<FName, FDiaryEntry> Diary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TArray<FString> UnlockedCategories;

	UPROPERTY(EditAnywhere)
	bool bIsInDebugMode;

public:	

	UTiDiaryComponent();
	
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetUnlockedCategories() const;

	UFUNCTION(BlueprintCallable)
	void AddDiaryEntry(FName EntryId);

	UFUNCTION(BlueprintCallable)
	void ClosePopUp();

	UFUNCTION(BlueprintCallable)
	void GetEntryDataByCategory(FString Category, TArray<FIndexData>& OutData) const;

	UFUNCTION(BlueprintCallable)
	bool GetEntryById(FName Id, FDiaryEntry& Data) const;

	UPROPERTY(BlueprintAssignable)
	FOnDiaryEntryAdded OnDiaryEntryAdded;
};
