﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Performance/GiltPerformanceSettings.h"
#include "Engine/PlatformSettings.h"


UGiltPlatformSpecificRenderingSettings::UGiltPlatformSpecificRenderingSettings()
{
	MobileFrameRateLimits.Append({ 20, 30, 45, 60, 90, 120 });
}

const UGiltPlatformSpecificRenderingSettings* UGiltPlatformSpecificRenderingSettings::Get()
{
	UGiltPlatformSpecificRenderingSettings* Result = UPlatformSettingsManager::Get().GetSettingsForPlatform<ThisClass>();
	check(Result);
	return Result;
}

//////////////////////////////////////////////////////////////////////

UGiltPerformanceSettings::UGiltPerformanceSettings()
{
	PerPlatformSettings.Initialize(UGiltPlatformSpecificRenderingSettings::StaticClass());

	CategoryName = TEXT("Game");

	DesktopFrameRateLimits.Append({ 30, 60, 120, 144, 160, 165, 180, 200, 240, 360 });

	// Default to all stats are allowed
	FGiltPerformanceStatGroup& StatGroup = UserFacingPerformanceStats.AddDefaulted_GetRef();
	for (EGiltDisplayablePerformanceStat PerfStat : TEnumRange<EGiltDisplayablePerformanceStat>())
	{
		StatGroup.AllowedStats.Add(PerfStat);
	}
}