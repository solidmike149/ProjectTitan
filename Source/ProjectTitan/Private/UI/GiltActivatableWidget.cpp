// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GiltActivatableWidget.h"

#include "Input/CommonInputMode.h"

TOptional<FUIInputConfig> UGiltActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case ETiWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case ETiWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case ETiWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case ETiWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}
