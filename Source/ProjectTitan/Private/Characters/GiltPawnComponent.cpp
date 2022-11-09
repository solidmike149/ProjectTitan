// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GiltPawnComponent.h"

UGiltPawnComponent::UGiltPawnComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}
