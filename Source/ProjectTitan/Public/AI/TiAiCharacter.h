// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/TiTargetInterface.h"
#include "TiAiCharacter.generated.h"

class UTiHealthSet;
class UGameplayEffect;
class UTiGameplayAbility;
class UTiAbilitySystemComponent;
class UWidgetComponent;

UCLASS()
class PROJECTTITAN_API ATiAiCharacter : public ACharacter, public IAbilitySystemInterface, public ITiTargetInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* TargetWidget;

	UPROPERTY(BlueprintReadWrite)
	AActor* Player;

	UPROPERTY(BlueprintReadOnly)
	UTiAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UTiHealthSet* HealthSet;

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
	
public:

	virtual void BeginPlay() override;

	void Tracking(float InterpSpeed);

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	ATiAiCharacter();
	
};
