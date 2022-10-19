// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TiDiary.generated.h"

class UCommonListView;
class UImage;
class UButton;

enum class EEntryCategory : uint8;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiDiary : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnIndexSelected(FName IndexId);

protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCommonListView* IndexList;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CloseButton;
};
