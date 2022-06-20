// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "TiCharacterBase.generated.h"

class UTiAbilitySystemComponent;
class UGameplayEffect;
class UTiGameplayAbility;

UCLASS()
class PROJECTTITAN_API ATiCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	ATiCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	UTiAbilitySystemComponent* AbilitySystemComponent;
	
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

	virtual void Die();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	UAnimMontage* DeathMontage;
	

};
