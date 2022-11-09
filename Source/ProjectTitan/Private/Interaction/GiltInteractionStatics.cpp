// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/GiltInteractionStatics.h"

#include "Interaction/GiltInteractableTargetInterface.h"

UGiltInteractionStatics::UGiltInteractionStatics()
	: Super(FObjectInitializer::Get())
{
}

AActor* UGiltInteractionStatics::GetActorFromInteractableTarget(TScriptInterface<IGiltInteractableTargetInterface> InteractableTarget)
{
	if (UObject* Object = InteractableTarget.GetObject())
	{
		if (AActor* Actor = Cast<AActor>(Object))
		{
			return Actor;
		}
		else if (UActorComponent* ActorComponent = Cast<UActorComponent>(Object))
		{
			return ActorComponent->GetOwner();
		}
		else
		{
			unimplemented();
		}
	}

	return nullptr;
}

void UGiltInteractionStatics::GetInteractableTargetsFromActor(AActor* Actor, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets)
{
	// If the actor is directly interactable, return that.
	TScriptInterface<IGiltInteractableTargetInterface> InteractableActor(Actor);
	if (InteractableActor)
	{
		OutInteractableTargets.Add(InteractableActor);
	}

	// If the actor isn't interactable, it might have a component that has a interactable interface.
	TArray<UActorComponent*> InteractableComponents = Actor ? Actor->GetComponentsByInterface(UGiltInteractableTargetInterface::StaticClass()) : TArray<UActorComponent*>();
	for (UActorComponent* InteractableComponent : InteractableComponents)
	{
		OutInteractableTargets.Add(TScriptInterface<IGiltInteractableTargetInterface>(InteractableComponent));
	}
}

void UGiltInteractionStatics::AppendInteractableTargetsFromOverlapResults(const TArray<FOverlapResult>& OverlapResults, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets)
{
	for (const FOverlapResult& Overlap : OverlapResults)
	{
		TScriptInterface<IGiltInteractableTargetInterface> InteractableActor(Overlap.GetActor());
		if (InteractableActor)
		{
			OutInteractableTargets.AddUnique(InteractableActor);
		}

		TScriptInterface<IGiltInteractableTargetInterface> InteractableComponent(Overlap.GetComponent());
		if (InteractableComponent)
		{
			OutInteractableTargets.AddUnique(InteractableComponent);
		}
	}
}

void UGiltInteractionStatics::AppendInteractableTargetsFromHitResult(const FHitResult& HitResult, TArray<TScriptInterface<IGiltInteractableTargetInterface>>& OutInteractableTargets)
{
	TScriptInterface<IGiltInteractableTargetInterface> InteractableActor(HitResult.GetActor());
	if (InteractableActor)
	{
		OutInteractableTargets.AddUnique(InteractableActor);
	}

	TScriptInterface<IGiltInteractableTargetInterface> InteractableComponent(HitResult.GetComponent());
	if (InteractableComponent)
	{
		OutInteractableTargets.AddUnique(InteractableComponent);
	}
}
