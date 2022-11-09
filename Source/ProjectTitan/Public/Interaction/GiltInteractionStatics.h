// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltInteractionStatics.generated.h"

class IGiltInteractableTargetInterface;
/**
 * 
 */
UCLASS()
class UGiltInteractionStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UGiltInteractionStatics();
	
	UFUNCTION(BlueprintCallable)
	static AActor* GetActorFromInteractableTarget(TScriptInterface<IGiltInteractableTargetInterface> InteractableTarget);

	UFUNCTION(BlueprintCallable)
	static void GetInteractableTargetsFromActor(AActor* Actor, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets);

	static void AppendInteractableTargetsFromOverlapResults(const TArray<FOverlapResult>& OverlapResults, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets);
	static void AppendInteractableTargetsFromHitResult(const FHitResult& HitResult, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets);
};
