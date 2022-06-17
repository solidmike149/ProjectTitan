// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/TiAsyncTaskTagsAddedRemoved.h"

UTiAsyncTaskTagsAddedRemoved* UTiAsyncTaskTagsAddedRemoved::ListenForGameplayTagAddedOrRemoved(UAbilitySystemComponent * AbilitySystemComponent, FGameplayTagContainer InTags)
{
	UTiAsyncTaskTagsAddedRemoved* ListenForGameplayTagAddedRemoved = NewObject<UTiAsyncTaskTagsAddedRemoved>();
	ListenForGameplayTagAddedRemoved->AbilitySystemComponent = AbilitySystemComponent;
	ListenForGameplayTagAddedRemoved->Tags = InTags;

	if (!IsValid(AbilitySystemComponent) || InTags.Num() < 1)
	{
		ListenForGameplayTagAddedRemoved->EndTask();
		return nullptr;
	}

	TArray<FGameplayTag> TagArray;
	InTags.GetGameplayTagArray(TagArray);
	
	for (FGameplayTag Tag : TagArray)
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved).AddUObject(ListenForGameplayTagAddedRemoved, &UTiAsyncTaskTagsAddedRemoved::TagChanged);
	}

	return ListenForGameplayTagAddedRemoved;
}

void UTiAsyncTaskTagsAddedRemoved::EndTask()
{
	if (IsValid(AbilitySystemComponent))
	{
		TArray<FGameplayTag> TagArray;
		Tags.GetGameplayTagArray(TagArray);

		for (FGameplayTag Tag : TagArray)
		{
			AbilitySystemComponent->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void UTiAsyncTaskTagsAddedRemoved::TagChanged(const FGameplayTag Tag, int32 NewCount)
{
	if (NewCount > 0)
	{
		OnTagAdded.Broadcast(Tag);
	}
	else
	{
		OnTagRemoved.Broadcast(Tag);
	}
}