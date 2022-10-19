// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "TiCategoryEntry.generated.h"

class UTextBlock;
enum class EEntryCategory : uint8;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnClickedCategory, FString, Category);

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiCategoryEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	
	FOnClickedCategory OnClicked;
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MainButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CategoryText;

	UPROPERTY(BlueprintReadWrite)
	FString Category;

	UFUNCTION()
	void OnButtonClicked();
};
