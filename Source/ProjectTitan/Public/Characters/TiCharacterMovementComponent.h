// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TiCharacterMovementComponent.generated.h"

PROJECTTITAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_MovementStopped);

/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UTiCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UTiCharacterMovementComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprint")
	float SprintSpeedMultiplier;

	bool RequestToStartSprinting;
	
	virtual float GetMaxSpeed() const override;
	
	// Sprint
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StartSprinting();
	
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void StopSprinting();
};
