// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "UI/TiIndexData.h"
#include "TiDiaryComponent.generated.h"

UENUM(BlueprintType)
enum class EEntryCategory : uint8
{
	None,
	Murales,
	CortesDiaryPages,
	Scrolls,
	Bodies,
	Training,
	Boss,
	Objects,
	Locations
};

USTRUCT(BlueprintType)
struct FDiaryEntry : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EEntryCategory Category;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Icon;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDiaryEntryAdded, UTiDiaryComponent*, Istigator, const FDiaryEntry&, DiaryEntry);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTTITAN_API UTiDiaryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataTable* DiaryTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, FDiaryEntry> Diary;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<EEntryCategory> UnlockedCategories;

public:	

	UTiDiaryComponent();
	
	UFUNCTION(BlueprintCallable)
	TArray<EEntryCategory> GetUnlockedCategories() const;

	UFUNCTION(BlueprintCallable)
	void AddDiaryEntry(FName EntryId);

	UFUNCTION(BlueprintCallable)
	void ClosePopUp();

	UFUNCTION(BlueprintCallable)
	void GetEntryDataByCategory(EEntryCategory Category, TArray<FIndexData>& OutData) const;

	UFUNCTION(BlueprintCallable)
	bool GetEntryById(FName Id, FDiaryEntry& Data) const;

	UFUNCTION(BlueprintCallable)
	TArray<FText> GetEntryTitlesByCategory(EEntryCategory Category) const;

	UPROPERTY(BlueprintAssignable)
	FOnDiaryEntryAdded OnDiaryEntryAdded;
};
