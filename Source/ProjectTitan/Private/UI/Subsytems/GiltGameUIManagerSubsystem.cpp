// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Subsytems/GiltGameUIManagerSubsystem.h"

UGiltGameUIManagerSubsystem::UGiltGameUIManagerSubsystem()
{
}

void UGiltGameUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGiltGameUIManagerSubsystem::Tick), 0.0f);
}

void UGiltGameUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
}

bool UGiltGameUIManagerSubsystem::Tick(float DeltaTime)
{
	SyncRootLayoutVisibilityToShowHUD();
	
	return true;
}

void UGiltGameUIManagerSubsystem::SyncRootLayoutVisibilityToShowHUD()
{
	/*if (const UGameUIPolicy* Policy = GetCurrentUIPolicy())
	{
		for (const ULocalPlayer* LocalPlayer : GetGameInstance()->GetLocalPlayers())
		{
			bool bShouldShowUI = true;
			
			if (const APlayerController* PC = LocalPlayer->GetPlayerController(GetWorld()))
			{
				const AHUD* HUD = PC->GetHUD();

				if (HUD && !HUD->bShowHUD)
				{
					bShouldShowUI = false;
				}
			}

			if (UPrimaryGameLayout* RootLayout = Policy->GetRootLayout(CastChecked<UCommonLocalPlayer>(LocalPlayer)))
			{
				const ESlateVisibility DesiredVisibility = bShouldShowUI ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed;
				if (DesiredVisibility != RootLayout->GetVisibility())
				{
					RootLayout->SetVisibility(DesiredVisibility);	
				}
			}
		}
	}*/
}

