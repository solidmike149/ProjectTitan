// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GiltPlayerController.h"

#include "AbilitySystem/GiltAbilitySystemComponent.h"
#include "Development/GiltDeveloperSettings.h"
#include "Player/GiltCheatManager.h"
#include "Player/GiltPlayerState.h"
#include "UI/GiltHUD.h"

AGiltPlayerController::AGiltPlayerController(const FObjectInitializer& ObjectInitializer)
{

#if USING_CHEAT_MANAGER
	CheatClass = UGiltCheatManager::StaticClass();
#endif // #if USING_CHEAT_MANAGER
}

AGiltPlayerState* AGiltPlayerController::GetGiltPlayerState() const
{
	return CastChecked<AGiltPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

AGiltHUD* AGiltPlayerController::GetGiltHUD() const
{
	return CastChecked<AGiltHUD>(GetHUD(), ECastCheckedType::NullAllowed);
}



void AGiltPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

#if WITH_EDITOR
	if (GIsEditor && (InPawn != nullptr) && (GetPawn() == InPawn))
	{
		for (const FGiltCheatToRun& CheatRow : GetDefault<UGiltDeveloperSettings>()->CheatsToRun)
		{
			if (CheatRow.Phase == ECheatExecutionTime::OnPlayerPawnPossession)
			{
				ConsoleCommand(CheatRow.Cheat, /*bWriteToLog=*/ true);
			}
		}
	}
#endif
}

UGiltAbilitySystemComponent* AGiltPlayerController::GetGiltAbilitySystemComponent() const
{
	const AGiltPlayerState* GiltPS = GetGiltPlayerState();
	return (GiltPS ? GiltPS->GetGiltAbilitySystemComponent() : nullptr);
}

void AGiltPlayerController::AddCheats(bool bForce)
{
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

void AGiltPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		GiltASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
