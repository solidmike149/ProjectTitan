// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/TiAsyncTaskAttributeChanged.h"

UTiAsyncTaskAttributeChanged* UTiAsyncTaskAttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UTiAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UTiAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UTiAsyncTaskAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UTiAsyncTaskAttributeChanged * UTiAsyncTaskAttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UTiAsyncTaskAttributeChanged* WaitForAttributeChangedTask = NewObject<UTiAsyncTaskAttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UTiAsyncTaskAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UTiAsyncTaskAttributeChanged::EndTask()
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UTiAsyncTaskAttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}