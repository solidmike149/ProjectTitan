// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TiReloadPoint.h"

#include "Components/BoxComponent.h"

// Sets default values
ATiReloadPoint::ATiReloadPoint()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	MeshComp->SetupAttachment(RootComponent);
}
