// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TiDiary.generated.h"

class UButton;
class UListView;
class UImage;
enum class EEntryCategory : uint8;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiDiary : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnCategoryChanged(EEntryCategory Category);

	UFUNCTION(BlueprintNativeEvent)
	void OnIndexSelected(FName IndexId);

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* CategoryList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* IndexList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CloseButton;
};
