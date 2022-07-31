// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceSystem/TiRemoteTrace.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "NiagaraComponent.h"
#include "../../../../../../Program Files/Epic Games/UE_4.27/Engine/Plugins/Animation/RigLogic/Source/RigLogicLib/Public/pma/ScopedPtr.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATiRemoteTrace::ATiRemoteTrace()
{

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");
	NiagaraComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}



void ATiRemoteTrace::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UShapeComponent*> Collisions;
	
	GetComponents(Collisions);

	for (UShapeComponent* Collision : Collisions)
	{
		if(Collision && Collision != SphereComponent)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s : CollisionFound"), *this->GetFName().ToString())
			Collision->OnComponentHit.AddDynamic(this, &ATiRemoteTrace::OnComponentHit);
		}
	}
}

void ATiRemoteTrace::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(Range);
}

void ATiRemoteTrace::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDamage(OtherActor);

	SetLifeSpan(0.01f);
}

void ATiRemoteTrace::SetRange(float NewRange)
{
	Range = NewRange;
}

void ATiRemoteTrace::SetSpeed(float NewSpeed)
{
	ProjectileMovementComponent->InitialSpeed = NewSpeed;
}
