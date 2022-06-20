// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiShield.generated.h"

class UBoxComponent;
UCLASS()
class PROJECTTITAN_API ATiShield : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATiShield();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MainMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* RightCover;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LeftCover;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* TraceBegin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* TraceEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* WeakPoint;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeStatus(bool IsVulnerable);
};
