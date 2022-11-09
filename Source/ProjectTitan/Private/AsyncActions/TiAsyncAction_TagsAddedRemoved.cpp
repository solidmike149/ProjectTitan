// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/TiAsyncAction_TagsAddedRemoved.h"

UTiAsyncAction_TagsAddedRemoved* UTiAsyncAction_TagsAddedRemoved::ListenForGameplayTagAddedOrRemoved(UAbilitySystemComponent * AbilitySystemComponent, FGameplayTagContainer InTags)
{
	UTiAsyncAction_TagsAddedRemoved* ListenForGameplayTagAddedRemoved = NewObject<UTiAsyncAction_TagsAddedRemoved>();
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
		AbilitySystemComponent->RegisterGameplayTagEvent(Tag, EGameplayTagEventType::NewOrRemoved).AddUObject(ListenForGameplayTagAddedRemoved, &UTiAsyncAction_TagsAddedRemoved::TagChanged);
	}

	return ListenForGameplayTagAddedRemoved;
}

void UTiAsyncAction_TagsAddedRemoved::EndTask()
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
	MarkAsGarbage();
}

void UTiAsyncAction_TagsAddedRemoved::TagChanged(const FGameplayTag Tag, int32 NewCount)
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
