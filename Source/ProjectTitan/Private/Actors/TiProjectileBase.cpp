// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TiProjectileBase.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATiProjectileBase::ATiProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;
	
	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComponent");
	ParticleComp->SetupAttachment(RootComponent);
	
}

