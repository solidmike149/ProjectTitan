// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TiShield.generated.h"

class UTiTraceComponent;
class UBoxComponent;
UCLASS()
class PROJECTTITAN_API ATiShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiShield();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* MainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RightCover;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LeftCover;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* WeakPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UTiTraceComponent* TraceComponent;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeStatus(bool IsVulnerable);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ActivateTrace(FGameplayTag EventTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DeactivateTrace();
};
