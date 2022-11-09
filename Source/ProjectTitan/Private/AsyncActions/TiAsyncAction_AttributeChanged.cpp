// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/TiAsyncAction_AttributeChanged.h"

UTiAsyncAction_AttributeChanged* UTiAsyncAction_AttributeChanged::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	UTiAsyncAction_AttributeChanged* WaitForAttributeChangedTask = NewObject<UTiAsyncAction_AttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UTiAsyncAction_AttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}

UTiAsyncAction_AttributeChanged * UTiAsyncAction_AttributeChanged::ListenForAttributesChange(UAbilitySystemComponent * AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	UTiAsyncAction_AttributeChanged* WaitForAttributeChangedTask = NewObject<UTiAsyncAction_AttributeChanged>();
	WaitForAttributeChangedTask->AbilitySystemComponent = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &UTiAsyncAction_AttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}

void UTiAsyncAction_AttributeChanged::EndTask()
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

void UTiAsyncAction_AttributeChanged::AttributeChanged(const FOnAttributeChangeData & Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
