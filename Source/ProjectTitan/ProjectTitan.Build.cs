// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectTitan : ModuleRules
{
	public ProjectTitan(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {  
			"Core",
			"CoreUObject",
			"ApplicationCore",
			"Engine",
			"InputCore",
			"GameplayAbilities",
			"Niagara",
			"EnhancedInput"
		});
		PrivateDependencyModuleNames.AddRange(new string[] {
			"Slate",
			"SlateCore",
			"GameplayTags",
			"GameplayTasks",
			"AIModule",
			"NavigationSystem",
			"UMG",
			"CommonUI",
			"CommonInput",
			"CommonLoadingScreen",
			"CommonGame",
			"ModularGameplay",
			"ModularGameplayActors",
			"GameFeatures",
			"UIExtension",
			"AudioMixer",
			"AudioModulation"
		});
	}
}
