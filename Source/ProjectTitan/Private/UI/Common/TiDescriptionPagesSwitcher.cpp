// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Common/TiDescriptionPagesSwitcher.h"

#include "Groups/CommonButtonGroupBase.h"
#include "CommonWidgetCarousel.h"
#include "Components/WidgetSwitcher.h"
#include "Input/CommonUIInputTypes.h"


void UTiDescriptionPagesSwitcher::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (bAutoListenForInput)
	{
		SetListeningForInput(true);
	}
}


void UTiDescriptionPagesSwitcher::SetListeningForInput(bool bShouldListen)
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


void UTiDescriptionPagesSwitcher::UpdateBindings()
{
	// New input system binding flow
	if (bIsListeningForInput)
	{
		NextTabActionHandle = RegisterUIActionBinding(FBindUIActionArgs(NextTabInputActionData, false, FSimpleDelegate::CreateUObject(this, &UTiDescriptionPagesSwitcher::HandleNextTabAction)));
		PrevTabActionHandle = RegisterUIActionBinding(FBindUIActionArgs(PreviousTabInputActionData, false, FSimpleDelegate::CreateUObject(this, &UTiDescriptionPagesSwitcher::HandlePreviousTabAction)));
	}
	else
	{
		NextTabActionHandle.Unregister();
		PrevTabActionHandle.Unregister();
	}
}


void UTiDescriptionPagesSwitcher::HandleNextTabAction()
{
	int32 Pages = WidgetSwitcher->GetNumWidgets();
	
	if(Pages > 1)
	{
		int32 NextIndex = WidgetSwitcher->GetActiveWidgetIndex() + 1;
		
		if(NextIndex <= Pages)
		{
			WidgetSwitcher->SetActiveWidgetIndex(NextIndex);
		}
	}
}


void UTiDescriptionPagesSwitcher::HandlePreviousTabAction()
{
	int32 Pages = WidgetSwitcher->GetNumWidgets();

	if(Pages > 1)
	{
		int32 NextIndex = WidgetSwitcher->GetActiveWidgetIndex() - 1;
		
		if(NextIndex >= 0)
		{
			WidgetSwitcher->SetActiveWidgetIndex(NextIndex);
		}
	}
}


