// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "TiDialogWindow.generated.h"


class UDialogData;
/**
 * 
 */
UCLASS(Abstract)
class PROJECTTITAN_API UTiDialogWindow : public UCommonActivatableWidget
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = TabList)
	virtual void SetListeningForInput(bool bShouldListen);

protected:
	
	// UUserWidget interface
	virtual void NativeConstruct() override;
	// End UUserWidget

	virtual void UpdateBindings();
	
	/** The data id representing the dialog to display */
	UPROPERTY(Transient, BlueprintReadWrite, Category = "Dialogs")
	FPrimaryAssetId DialogData;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Dialogs")
	UDataTable* DialogLines;

	UPROPERTY(Transient, BlueprintReadWrite, Category = "Dialogs")
	TMap<FString, UTexture2D*> Portraits;

	/** The input action to listen for causing the dialog tab to be advance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle NextPageInputActionData;

	/** Whether to register to handle tab list input immediately upon construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PageSwitcher, meta = (ExposeOnSpawn = "true"))
	bool bAutoListenForInput;

	/** Is the tab list currently listening for tab input actions? */
	bool bIsListeningForInput = false;

	UFUNCTION(BlueprintImplementableEvent)
	void HandleNextPageAction();

private:

	FUIActionBindingHandle NextPageActionHandle;

public:

	UFUNCTION(BlueprintCallable)
	void SetDialogData(FPrimaryAssetId NewDialogData);
};
