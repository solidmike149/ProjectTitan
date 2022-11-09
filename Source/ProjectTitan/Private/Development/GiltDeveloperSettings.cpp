// Fill out your copyright notice in the Description page of Project Settings.


#include "Development/GiltDeveloperSettings.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Misc/App.h"
#include "Widgets/Notifications/SNotificationList.h"

#define LOCTEXT_NAMESPACE "GiltCheats"

UGiltDeveloperSettings::UGiltDeveloperSettings()
{
}

FName UGiltDeveloperSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}

#if WITH_EDITOR

void UGiltDeveloperSettings::OnPlayInEditorStarted() const
{
	// Show a notification toast to remind the user that there's an experience override set
	if (ExperienceOverride.IsValid())
	{
		FNotificationInfo Info(FText::Format(
			LOCTEXT("ExperienceOverrideActive", "Developer Settings Override\nExperience {0}"),
			FText::FromName(ExperienceOverride.PrimaryAssetName)
		));
		Info.ExpireDuration = 2.0f;
		FSlateNotificationManager::Get().AddNotification(Info);
	}
}

#endif

#undef LOCTEXT_NAMESPACE
