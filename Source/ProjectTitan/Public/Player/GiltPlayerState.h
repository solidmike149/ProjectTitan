// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ModularPlayerState.h"
#include "GiltPlayerState.generated.h"

class UGiltExperienceDefinition;
class UGiltPawnData;
class UAbilitySystemComponent;
class AGiltPlayerController;
class UGiltAbilitySystemComponent;

/**
 * AGiltPlayerState
 *
 *	Base player state class used by this project.
 */
UCLASS(Config = Game)
class PROJECTTITAN_API AGiltPlayerState : public AModularPlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AGiltPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Gilt|PlayerState")
	AGiltPlayerController* GetGiltPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "Gilt|PlayerState")
	UGiltAbilitySystemComponent* GetGiltAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }

	void SetPawnData(const UGiltPawnData* InPawnData);

	//~AActor interface
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	static const FName NAME_LyraAbilityReady;

private:

	void OnExperienceLoaded(const UGiltExperienceDefinition* CurrentExperience);

protected:

	UPROPERTY()
	const UGiltPawnData* PawnData;

private:

	// The ability system component sub-object used by player characters.
	UPROPERTY(VisibleAnywhere, Category = "Gilt|PlayerState")
	UGiltAbilitySystemComponent* AbilitySystemComponent;
};
