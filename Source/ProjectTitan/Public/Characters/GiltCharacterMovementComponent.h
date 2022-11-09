// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GiltCharacterMovementComponent.generated.h"

PROJECTTITAN_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Gameplay_MovementStopped);

/**
 * UGiltCharacterMovementComponent
 *
 *	The base character movement component class used by this project.
 */
UCLASS(Config = Game)
class PROJECTTITAN_API UGiltCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	/** Tags (applied on the ASC) that block the movement for the owner */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MovementBlock")
	FGameplayTagContainer MovementBlockingTag;

	UGiltCharacterMovementComponent();
	
	virtual float GetMaxSpeed() const override;
};
