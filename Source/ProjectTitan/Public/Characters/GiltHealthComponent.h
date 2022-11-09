// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "GiltHealthComponent.generated.h"

struct FGameplayEffectSpec;
struct FOnAttributeChangeData;
class UTiHealthSet;
class UTiAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGiltHealth_DeathEvent, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGiltHealth_AttributeChanged, UGiltHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * EGiltDeathState
 *
 *	Defines current state of death.
 */
UENUM(BlueprintType)
enum class EGiltDeathState : uint8
{
	NotDead = 0,
	DeathStarted,
	DeathFinished
};

/**
 * UTiHealthComponent
 *
 *	An actor component used to handle anything related to health.
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class PROJECTTITAN_API UGiltHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	UGiltHealthComponent(const FObjectInitializer& ObjectInitializer);
	
	/** Returns the health component if one exists on the specified actor. */
	UFUNCTION(BlueprintPure, Category = "Health")
	static UGiltHealthComponent* FindHealthComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGiltHealthComponent>() : nullptr); }
	
	/** Initialize the component using an ability system component. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void InitializeWithAbilitySystem(UTiAbilitySystemComponent* InASC);
	
	/** Uninitialize the component, clearing any references to the ability system. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UninitializeFromAbilitySystem();
	
	/** Returns the current health value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() const;
	
	/** Returns the current maximum health value. */
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	EGiltDeathState GetDeathState() const { return DeathState; }

	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Health", Meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool IsDeadOrDying() const { return (DeathState > EGiltDeathState::NotDead); }

	/** Begins the death sequence for the owner. */
	virtual void StartDeath();

	/** Ends the death sequence for the owner. */
	virtual void FinishDeath();
	

	/** Delegate fired when the health value has changed. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_AttributeChanged OnHealthChanged;

	/** Delegate fired when the max health value has changed. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_AttributeChanged OnMaxHealthChanged;

	/** Delegate fired when the death sequence has started. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_DeathEvent OnDeathStarted;

	/** Delegate fired when the death sequence has finished. */
	UPROPERTY(BlueprintAssignable)
	FGiltHealth_DeathEvent OnDeathFinished;

protected:

	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude);
	
	// Ability system used by this component.
	UPROPERTY()
	UTiAbilitySystemComponent* AbilitySystemComponent;

	// Health set used by this component.
	UPROPERTY()
	const UTiHealthSet* HealthSet;

	// Replicated state used to handle dying.
	UPROPERTY()
	EGiltDeathState DeathState;
};
