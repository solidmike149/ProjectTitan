// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "GiltPlayerController.generated.h"


class UGiltAbilitySystemComponent;
class AGiltHUD;
/**
 * AGiltPlayerController
 *
 *	The base player controller class used by this project.
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class PROJECTTITAN_API AGiltPlayerController : public ACommonPlayerController
{
	GENERATED_BODY()


	AGiltPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Gilt|PlayerController")
	AGiltHUD* GetGiltHUD() const;

	//~APlayerController interface
	virtual void AddCheats(bool bForce) override;
	
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	//~End of APlayerController interface
};
