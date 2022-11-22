// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/IndicatorSystem/GiltIndicatorManagerComponent.h"

#include "UI/IndicatorSystem/GiltIndicatorDescriptor.h"


UGiltIndicatorManagerComponent::UGiltIndicatorManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAutoRegister = true;
	bAutoActivate = true;
}

/*static*/ UGiltIndicatorManagerComponent* UGiltIndicatorManagerComponent::GetComponent(AController* Controller)
{
	if (Controller)
	{
		return Controller->FindComponentByClass<UGiltIndicatorManagerComponent>();
	}

	return nullptr;
}

void UGiltIndicatorManagerComponent::AddIndicator(UGiltIndicatorDescriptor* IndicatorDescriptor)
{
	IndicatorDescriptor->SetIndicatorManagerComponent(this);
	OnIndicatorAdded.Broadcast(IndicatorDescriptor);
	Indicators.Add(IndicatorDescriptor);
}

void UGiltIndicatorManagerComponent::RemoveIndicator(UGiltIndicatorDescriptor* IndicatorDescriptor)
{
	if (IndicatorDescriptor)
	{
		ensure(IndicatorDescriptor->GetIndicatorManagerComponent() == this);
	
		OnIndicatorRemoved.Broadcast(IndicatorDescriptor);
		Indicators.Remove(IndicatorDescriptor);
	}
}