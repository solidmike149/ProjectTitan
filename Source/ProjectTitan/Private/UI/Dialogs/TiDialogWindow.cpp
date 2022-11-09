// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Dialogs/TiDialogWindow.h"

#include "Input/CommonUIInputTypes.h"

void UTiDialogWindow::NativeConstruct()
{
	
	if (bAutoListenForInput)
	{
		SetListeningForInput(true);
	}
}


void UTiDialogWindow::SetListeningForInput(bool bShouldListen)
{
	if (GetUISubsystem() == nullptr)
	{
		// Shutting down
		return;
	}

	if (bShouldListen != bIsListeningForInput)
	{
		bIsListeningForInput = bShouldListen;
		UpdateBindings();
	}
}


void UTiDialogWindow::UpdateBindings()
{
	// New input system binding flow
	if (bIsListeningForInput)
	{
		NextPageActionHandle = RegisterUIActionBinding(FBindUIActionArgs(NextPageInputActionData, false, FSimpleDelegate::CreateUObject(this, &UTiDialogWindow::HandleNextPageAction)));
	}
	else
	{
		NextPageActionHandle.Unregister();
	}
}

void UTiDialogWindow::SetDialogData(FPrimaryAssetId NewDialogData)
{
	DialogData = NewDialogData;
}
