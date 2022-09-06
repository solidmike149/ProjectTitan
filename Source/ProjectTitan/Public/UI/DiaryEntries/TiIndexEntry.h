// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "TiIndexEntry.generated.h"


class UTextBlock;
class UButton;

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnClickedIndex, FName, Id);
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiIndexEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FOnClickedIndex OnClicked;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MainButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* IndexText;

	UPROPERTY(BlueprintReadWrite)
	FName Id;

	UFUNCTION()
	void OnButtonClicked();
};
