// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceSystem/TiRemoteTrace.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "NiagaraComponent.h"
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

	TArray<UPrimitiveComponent*> Collisions;
	
	GetComponents(Collisions);

	for (UPrimitiveComponent* Collision : Collisions)
	{
		if(Collision)
		{
			Collision->OnComponentHit.AddDynamic(this, &ATiRemoteTrace::OnComponentHit);
		}
	}
}

void ATiRemoteTrace::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDamage(OtherActor);

	SetLifeSpan(0.01f);
}
