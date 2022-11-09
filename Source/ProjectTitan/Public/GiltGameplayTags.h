// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * FGiltGameplayTags
 *
 *	Singleton containing native gameplay tags.
 */
struct FGiltGameplayTags
{

	static const FGiltGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	static FGameplayTag FindTagByString(FString TagString, bool bMatchPartialString = false);
	
	FGameplayTag Ability_ActivateFail_IsDead;
	FGameplayTag Ability_ActivateFail_Cooldown;
	FGameplayTag Ability_ActivateFail_Cost;
	FGameplayTag Ability_ActivateFail_TagsBlocked;
	FGameplayTag Ability_ActivateFail_TagsMissing;
	FGameplayTag Ability_ActivateFail_ActivationGroup;

	FGameplayTag Ability_Behavior_SurvivesDeath;

	FGameplayTag InputTag_Move;

	FGameplayTag GameplayEvent_Death;
	FGameplayTag GameplayEvent_Reset;

	FGameplayTag SetByCaller_Damage;
	FGameplayTag SetByCaller_Heal;

	FGameplayTag Cheat_GodMode;
	FGameplayTag Cheat_UnlimitedHealth;
	
	FGameplayTag Status_Death;
	FGameplayTag Status_Death_Dying;
	FGameplayTag Status_Death_Dead;
	FGameplayTag Status_Aim;

	FGameplayTag Movement_Mode_Walking;
	FGameplayTag Movement_Mode_NavWalking;
	FGameplayTag Movement_Mode_Falling;
	FGameplayTag Movement_Mode_Swimming;
	FGameplayTag Movement_Mode_Flying;
	FGameplayTag Movement_Mode_Custom;

	TMap<uint8, FGameplayTag> MovementModeTagMap;


protected:

	void AddAllTags(UGameplayTagsManager& Manager);
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);
	void AddMovementModeTag(FGameplayTag& OutTag, const ANSICHAR* TagName, uint8 MovementMode);

private:

	static FGiltGameplayTags GameplayTags;
};

