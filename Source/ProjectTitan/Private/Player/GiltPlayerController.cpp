// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GiltPlayerController.h"
#include "Player/GiltCheatManager.h"
#include "UI/GiltHUD.h"

AGiltPlayerController::AGiltPlayerController(const FObjectInitializer& ObjectInitializer)
{

#if USING_CHEAT_MANAGER
	CheatClass = UGiltCheatManager::StaticClass();
#endif // #if USING_CHEAT_MANAGER
}

AGiltHUD* AGiltPlayerController::GetGiltHUD() const
{
	return CastChecked<AGiltHUD>(GetHUD(), ECastCheckedType::NullAllowed);
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
	// if (UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	// {
	// 	GiltASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	// }

	Super::PostProcessInput(DeltaTime, bGamePaused);
}
