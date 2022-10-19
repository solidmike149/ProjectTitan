// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Engine/DataTable.h"
#include "TiDescriptionPagesSwitcher.generated.h"

class UWidgetSwitcher;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiDescriptionPagesSwitcher : public UCommonUserWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = TabList)
	virtual void SetListeningForInput(bool bShouldListen);

protected:
	
	// UUserWidget interface
	virtual void NativeConstruct() override;
	// End UUserWidget

	virtual void UpdateBindings();

	/** The input action to listen for causing the next tab to be selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle NextTabInputActionData;

	/** The input action to listen for causing the previous tab to be selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle PreviousTabInputActionData;

	/** Whether to register to handle tab list input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;
	
	/** Is the tab list currently listening for tab input actions? */
	bool bIsListeningForInput = false;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

private:

	void HandleNextTabAction();
	void HandlePreviousTabAction();

	FUIActionBindingHandle NextTabActionHandle;
	FUIActionBindingHandle PrevTabActionHandle;
};
