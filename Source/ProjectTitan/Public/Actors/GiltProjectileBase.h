// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "GiltProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;

UCLASS(Abstract)
class PROJECTTITAN_API AGiltProjectileBase : public AActor
{
	GENERATED_BODY()

public:	

	AGiltProjectileBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = true), Category = "Range")
	float Range;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
};
