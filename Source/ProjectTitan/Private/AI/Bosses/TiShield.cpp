// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Bosses/TiShield.h"

#include "Components/BoxComponent.h"
#include "TraceSystem/TiTraceComponent.h"

// Sets default values
ATiShield::ATiShield()
{

	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MainMesh");
	RootComponent = MainMesh;

	RightCover = CreateDefaultSubobject<UStaticMeshComponent>("RightCover");
	RightCover->SetupAttachment(RootComponent);

	LeftCover = CreateDefaultSubobject<UStaticMeshComponent>("LeftCover");
	LeftCover->SetupAttachment(RootComponent);

	WeakPoint = CreateDefaultSubobject<UBoxComponent>("WeakPoint");
	WeakPoint->SetupAttachment(RootComponent);

	TraceComponent = CreateDefaultSubobject<UTiTraceComponent>("TraceComponent");
}
