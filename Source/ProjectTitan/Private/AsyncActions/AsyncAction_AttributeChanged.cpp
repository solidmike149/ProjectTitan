// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/AsyncAction_AttributeChanged.h"

UAsyncAction_AttributeChanged* UAsyncAction_AttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UAsyncAction_AttributeChanged* WaitForAttributeChangedTask = NewObject<UAsyncAction_AttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UAsyncAction_AttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UAsyncAction_AttributeChanged * UAsyncAction_AttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UAsyncAction_AttributeChanged* WaitForAttributeChangedTask = NewObject<UAsyncAction_AttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UAsyncAction_AttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UAsyncAction_AttributeChanged::EndTask()
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

void UAsyncAction_AttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
