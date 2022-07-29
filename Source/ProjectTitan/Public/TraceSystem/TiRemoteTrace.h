// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiRemoteTrace.generated.h"

class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS(Abstract)
class PROJECTTITAN_API ATiRemoteTrace : public AActor
{
	GENERATED_BODY()

public:

	ATiRemoteTrace();

	UPROPERTY(EditAnywhere)
	float Duration;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;
	
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable ,BlueprintImplementableEvent)
	void ApplyDamage(AActor* ActorToDamage);
};
