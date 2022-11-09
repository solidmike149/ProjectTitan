// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GiltCharacter.h"

#include "CommonInputSubsystem.h"
#include "AbilitySystem/GiltAbilitySystemComponent.h"
#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "Characters/GiltCharacterMovementComponent.h"
#include "Characters/GiltHealthComponent.h"
#include "Characters/GiltPawnExtensionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/GiltPlayerController.h"
#include "Player/GiltPlayerState.h"


AGiltCharacter::AGiltCharacter(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UGiltCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	PawnExtComponent = CreateDefaultSubobject<UGiltPawnExtensionComponent>("PawnExtensionComponent");
	PawnExtComponent->OnAbilitySystemInitialized_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemInitialized));
	PawnExtComponent->OnAbilitySystemUninitialized_Register(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnAbilitySystemUninitialized));

	HealthComponent = CreateDefaultSubobject<UGiltHealthComponent>("HealthComponent");
}

void AGiltCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
    HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);
}

AGiltPlayerController* AGiltCharacter::GetGiltPlayerController() const
{
	return CastChecked<AGiltPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

AGiltPlayerState* AGiltCharacter::GetGiltPlayerState() const
{
	return CastChecked<AGiltPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

UGiltAbilitySystemComponent* AGiltCharacter::GetGiltAbilitySystemComponent() const
{
	return Cast<UGiltAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* AGiltCharacter::GetAbilitySystemComponent() const
{
	return PawnExtComponent->GetGiltAbilitySystemComponent();
}

void AGiltCharacter::OnAbilitySystemInitialized()
{
	UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent();
	check(GiltASC);

	// TODO Uncomment
	//HealthComponent->InitializeWithAbilitySystem(GiltASC);

	//InitializeGameplayTags();
}

void AGiltCharacter::OnAbilitySystemUninitialized()
{
	HealthComponent->UninitializeFromAbilitySystem();
}

/*void AGiltCharacter::InitializeGameplayTags()
{
	// Clear tags that may be lingering on the ability system from the previous pawn.
	if (UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		const FGiltGameplayTags& GameplayTags = FGiltGameplayTags::Get();

		for (const TPair<uint8, FGameplayTag>& TagMapping : GameplayTags.MovementModeTagMap)
		{
			if (TagMapping.Value.IsValid())
			{
				GiltASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}

		for (const TPair<uint8, FGameplayTag>& TagMapping : GameplayTags.CustomMovementModeTagMap)
		{
			if (TagMapping.Value.IsValid())
			{
				GiltASC->SetLooseGameplayTagCount(TagMapping.Value, 0);
			}
		}

		UGiltCharacterMovementComponent* GiltMoveComp = CastChecked<UGiltCharacterMovementComponent>(GetCharacterMovement());
		SetMovementModeTag(GiltMoveComp->MovementMode, GiltMoveComp->CustomMovementMode, true);
	}
}*/

void AGiltCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (const UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		GiltASC->GetOwnedGameplayTags(TagContainer);
	}
}

bool AGiltCharacter::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	if (const UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		return GiltASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

bool AGiltCharacter::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		return GiltASC->HasAllMatchingGameplayTags(TagContainer);
	}

	return false;
}

bool AGiltCharacter::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	if (const UGiltAbilitySystemComponent* GiltASC = GetGiltAbilitySystemComponent())
	{
		return GiltASC->HasAnyMatchingGameplayTags(TagContainer);
	}

	return false;
}



void AGiltCharacter::OnDeathStarted(AActor*)
{
	DisableMovementAndCollision();
}

void AGiltCharacter::OnDeathFinished(AActor*)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void AGiltCharacter::DisableMovementAndCollision()
{
	if (Controller)
	{
		Controller->SetIgnoreMoveInput(true);
	}

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	check(CapsuleComp);
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();
}

void AGiltCharacter::DestroyDueToDeath()
{
	K2_OnDeathFinished();

	UninitAndDestroy();
}

void AGiltCharacter::UninitAndDestroy()
{

	DetachFromControllerPendingDestroy();
	SetLifeSpan(0.1f);
	
	//SetActorHiddenInGame(true);
}


