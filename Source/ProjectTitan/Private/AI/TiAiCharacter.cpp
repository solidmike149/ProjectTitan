// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TiAiCharacter.h"

#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "AbilitySystem/AttributeSets/TiHealthSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ATiAiCharacter::ATiAiCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}


void ATiAiCharacter::Tracking(float InterpSpeed)
{
	FRotator TargetRotation = FRotationMatrix::MakeFromX(Player->GetActorLocation() - GetActorLocation()).Rotator();
	
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation,
											GetWorld()->GetDeltaSeconds(), InterpSpeed);
	SetActorRotation(NewRotation);
}
