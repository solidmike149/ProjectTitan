// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "TiGA_PlayerShoot.generated.h"

class ATiProjectileBase;
/**
 * 
 */
UCLASS(Abstract)
class PROJECTTITAN_API UTiGA_PlayerShoot : public UTiGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Projectile")
	float ProjectileRange;

	/* Spawn origin Socket */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FName Socket;

	/* Range that will be added every Period */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float AddedRange;

	/* Projectile Spawned */
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ATiProjectileBase> ProjectileClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effect")
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

	UFUNCTION(BlueprintCallable)
	FVector AdjustRotation(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void ActualShoot(FVector TargetLocation);

public:

	UTiGA_PlayerShoot();
};
