// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltActivatableWidget.h"
#include "GiltHUDLayout.generated.h"

/**
 * Widget used to lay out the player's HUD
 */
UCLASS(Abstract, Blueprintable, Meta = (DisplayName = "Gilt HUD Layout", Category = "Gilt|HUD"))
class PROJECTTITAN_API UGiltHUDLayout : public UGiltActivatableWidget
{
	GENERATED_BODY()

public:

	UGiltHUDLayout(const FObjectInitializer& ObjectInitializer);

	virtual void NativeOnInitialized() override;

protected:
	
	void HandleEscapeAction();

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;
};
