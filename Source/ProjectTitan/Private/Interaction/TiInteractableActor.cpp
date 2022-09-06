// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/TiInteractableActor.h"

#include "Components/WidgetComponent.h"


ATiInteractableActor::ATiInteractableActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = MeshComp;

	HintWidget = CreateDefaultSubobject<UWidgetComponent>("HintWidgetComponent");
	HintWidget->SetupAttachment(RootComponent);

	PromptWidget = CreateDefaultSubobject<UWidgetComponent>("PromptWidgetComponent");
	PromptWidget->SetupAttachment(RootComponent);
}

