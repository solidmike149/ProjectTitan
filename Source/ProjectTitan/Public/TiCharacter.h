// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "GameFramework/Character.h"
#include "TiCharacter.generated.h"

class UTiPlayerSet;
class UTiHealthSet;
class UGameplayEffect;
class UTiGameplayAbility;
class UTiAbilitySystemComponent;
class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;

UCLASS()
class PROJECTTITAN_API ATiCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWidgetComponent* Widget;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	UTiAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	UTiHealthSet* HealthAttributeSet;

	UPROPERTY()
	UTiPlayerSet* PlayerAttributeSet;
	
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION()
	void Roll();

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
	virtual void OnDeathStarted(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec& EffectSpec, float EffectMagnitude);

	void DisableMovementAndCollision();
	
	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();
	
public:

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> Targets;

	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentTarget;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLocking;
	
	ATiCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void BindASCInput();
};
