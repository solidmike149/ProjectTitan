// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiReloadPoint.generated.h"

class UBoxComponent;
UCLASS()
class PROJECTTITAN_API ATiReloadPoint : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComp;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

public:
	
	ATiReloadPoint();
};
