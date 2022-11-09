// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Messaging/CommonGameDialog.h"
#include "GiltConfirmationScreen.generated.h"

class UCommonBorder;
class UDynamicEntryBox;
class UCommonRichTextBlock;
class UCommonTextBlock;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROJECTTITAN_API UGiltConfirmationScreen : public UCommonGameDialog
{
	GENERATED_BODY()

public:
	virtual void SetupDialog(UCommonGameDialogDescriptor* Descriptor, FCommonMessagingResultDelegate ResultCallback) override;
	virtual void KillDialog() override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void CloseConfirmationWindow(ECommonMessagingResult Result);

#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif

private:

	UFUNCTION()
	FEventReply HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent);

	FCommonMessagingResultDelegate OnResultCallback;

private:
	UPROPERTY(Meta = (BindWidget))
	UCommonTextBlock* Text_Title;

	UPROPERTY(Meta = (BindWidget))
	UCommonRichTextBlock* RichText_Description;

	UPROPERTY(Meta = (BindWidget))
	UDynamicEntryBox* EntryBox_Buttons;

	UPROPERTY(Meta = (BindWidget))
	UCommonBorder* Border_TapToCloseZone;

	UPROPERTY(EditDefaultsOnly, meta = (RowType = CommonInputActionDataBase))
	FDataTableRowHandle CancelAction;
};
