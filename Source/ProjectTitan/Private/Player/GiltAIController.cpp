// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GiltAIController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"


AGiltAIController::AGiltAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bWantsPlayerState = true;
	bStopAILogicOnUnposses = false;
}

void AGiltAIController::OnUnPossess()
{
	 /*
	 // Make sure the pawn that is being unpossessed doesn't remain our ASC's avatar actor
	if (APawn* PawnBeingUnpossessed = GetPawn())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PlayerState))
		{
			if (ASC->GetAvatarActor() == PawnBeingUnpossessed)
			{
				ASC->SetAvatarActor(nullptr);
			}
		}
	}
	*/
	
	Super::OnUnPossess();
}
