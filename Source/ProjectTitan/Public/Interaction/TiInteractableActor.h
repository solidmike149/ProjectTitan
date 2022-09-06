// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TiInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "TiInteractableActor.generated.h"

class UWidgetComponent;
UCLASS()
class PROJECTTITAN_API ATiInteractableActor : public AActor, public ITiInteractionInterface
{
	GENERATED_BODY()
	
public:
	
	ATiInteractableActor();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* HintWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* PromptWidget;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diary")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractionState InteractionState;
};
