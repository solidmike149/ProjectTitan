﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "ModularCharacter.h"
#include "SaveSystem/GiltSaveInterface.h"
#include "TiCharacter.generated.h"


class UGiltHealthComponent;
class UTiGameplayAbility;
class UTiHealthSet;
class UTiAbilitySystemComponent;

UCLASS(Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class PROJECTTITAN_API ATiCharacter : public AModularCharacter, public IAbilitySystemInterface, public IGiltSaveInterface
{
	GENERATED_BODY()

	protected:

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	UTiAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", Meta = (AllowPrivateAccess = "true"))
	UGiltHealthComponent* HealthComponent;
	
	UPROPERTY()
	UTiHealthSet* HealthAttributeSet;
	
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UTiGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	virtual void AddCharacterAbilities();
	
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	void RemoveCharacterAbilities();

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);
	
	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UninitAndDestroy();
	
	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();
	
public:

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Sets default values for this character's properties
	ATiCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
