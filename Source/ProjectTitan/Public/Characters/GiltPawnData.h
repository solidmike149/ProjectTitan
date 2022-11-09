// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GiltPawnData.generated.h"

class UGiltInputConfig;
class UGiltAbilityTagRelationshipMapping;
class UGiltAbilitySet;
/**
 * UGiltPawnData
 *
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "Gilt Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class UGiltPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UGiltPawnData(const FObjectInitializer& ObjectInitializer);

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gilt|Abilities")
	TArray<UGiltAbilitySet*> AbilitySets;

	// What mapping of ability tags to use for actions taking by this pawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gilt|Abilities")
	UGiltAbilityTagRelationshipMapping* TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gilt|Input")
	UGiltInputConfig* InputConfig;
};
