// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltPawnComponent.h"
#include "InputAction.h"
#include "Input/GiltMappableConfigPair.h"
#include "GiltHeroComponent.generated.h"

struct FLoadedMappableConfigPair;
struct FInputActionValue;
class UGiltInputConfig;

/**
 * UGiltHeroComponent
 *
 *	A component used to create a player controlled pawns.
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent), DisplayName= "HeroComponent")
class UGiltHeroComponent : public UGiltPawnComponent
{
	GENERATED_BODY()

public:

	UGiltHeroComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the hero component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Gilt|Hero")
	static UGiltHeroComponent* FindHeroComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltHeroComponent>() : nullptr); }

	void AddAdditionalInputConfig(const UGiltInputConfig* InputConfig);
	//void RemoveAdditionalInputConfig(const UGiltInputConfig* InputConfig);

	/** True if this has completed OnPawnReadyToInitialize so is prepared for late-added features */
	bool HasPawnInitialized() const;

	/** True if this player has sent the BindInputsNow event and is prepared for bindings */
	bool IsReadyToBindInputs() const;

	static const FName NAME_BindInputsNow;

protected:

	virtual void OnRegister() override;

	virtual bool IsPawnComponentReadyToInitialize() const override;
	void OnPawnReadyToInitialize();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void InitializePlayerInput(UInputComponent* PlayerInputComponent);

	void Input_AbilityInputTagTriggered(const FInputActionInstance& ActionInstance);

	void Input_Move(const FInputActionValue& InputActionValue);

	void OnInputConfigActivated(const FLoadedMappableConfigPair& ConfigPair);
	void OnInputConfigDeactivated(const FLoadedMappableConfigPair& ConfigPair);

	/**
	 * Input Configs that should be added to this player when initializing the input.
	 * If possible use the GameFeatureAction_AddInputConfig instead. 
	 */
	UPROPERTY(EditAnywhere)
	TArray<FMappableConfigPair> DefaultInputConfigs;

	// True when the pawn has fully finished initialization
	bool bPawnHasInitialized;

	// True when player input bindings have been applied, will never be true for non-players
	bool bReadyToBindInputs;
};
