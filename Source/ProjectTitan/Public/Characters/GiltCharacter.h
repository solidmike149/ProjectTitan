// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffect.h"
#include "ModularCharacter.h"
#include "SaveSystem/GiltSaveInterface.h"
#include "GiltCharacter.generated.h"

class UGiltPawnExtensionComponent;
class UGiltAbilitySystemComponent;
class AGiltPlayerState;
class AGiltPlayerController;
class UGiltHealthComponent;
class UTiGameplayAbility;
class UTiHealthSet;
class UTiAbilitySystemComponent;


/**
 * AGiltCharacter
 *
 *	The base character pawn class used by this project.
 *	Responsible for sending events to pawn components.
 *	New behavior should be added via pawn components when possible.
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class PROJECTTITAN_API AGiltCharacter : public AModularCharacter, public IAbilitySystemInterface, public IGameplayTagAssetInterface, public IGiltSaveInterface
{
	GENERATED_BODY()

public:

	AGiltCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Gilt|Character")
	AGiltPlayerController* GetGiltPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "Gilt|Character")
	AGiltPlayerState* GetGiltPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "Gilt|Character")
	UGiltAbilitySystemComponent* GetGiltAbilitySystemComponent() const;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//~IGameplayTagAssetInterface interface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;
	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;
	//~End of IGameplayTagAssetInterface

protected:

	//~AActor interface
	virtual void PostInitializeComponents() override;
	//~End of AActor interface

	virtual void OnAbilitySystemInitialized();
	virtual void OnAbilitySystemUninitialized();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void InitializeGameplayTags();

	// Begins the death sequence for the character (disables collision, disables movement, etc...)
	UFUNCTION()
	virtual void OnDeathStarted(AActor* OwningActor);

	// Ends the death sequence for the character (detaches controller, destroys pawn, etc...)
	UFUNCTION()
	virtual void OnDeathFinished(AActor* OwningActor);

	void DisableMovementAndCollision();
	void DestroyDueToDeath();
	void UninitAndDestroy();

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode) override;
	void SetMovementModeTag(EMovementMode MovementMode, uint8 CustomMovementMode, bool bTagEnabled);
	
	
	// Called when the death sequence for the character has completed
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeathFinished"))
	void K2_OnDeathFinished();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gilt|Character", Meta = (AllowPrivateAccess = "true"))
	UGiltPawnExtensionComponent* PawnExtComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gilt|Character", Meta = (AllowPrivateAccess = "true"))
	UGiltHealthComponent* HealthComponent;
};
