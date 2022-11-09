// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TiCharacter.h"

#include "CommonInputSubsystem.h"
#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "AbilitySystem/AttributeSets/TiHealthSet.h"
#include "Characters/GiltCharacterMovementComponent.h"
#include "Characters/GiltHealthComponent.h"
#include "Components/CapsuleComponent.h"

ATiCharacter::ATiCharacter(const FObjectInitializer& ObjectInitializer) :
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
	
	AbilitySystemComponent = CreateDefaultSubobject<UTiAbilitySystemComponent>("ActionComponent");

	HealthAttributeSet = CreateDefaultSubobject<UTiHealthSet>("HealthSet");

	HealthComponent = CreateDefaultSubobject<UGiltHealthComponent>("HealthComponent");
}

void ATiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	HealthComponent->OnDeathStarted.AddDynamic(this, &ThisClass::OnDeathStarted);
    HealthComponent->OnDeathFinished.AddDynamic(this, &ThisClass::OnDeathFinished);
}

void ATiCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		InitializeAttributes();

		AddStartupEffects();

		AddCharacterAbilities();
	}
}

void ATiCharacter::AddCharacterAbilities()
{
	for (TSubclassOf<UTiGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		if (StartupAbility)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s() Missing Ability %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		}
	}
}

void ATiCharacter::InitializeAttributes()
{
	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void ATiCharacter::AddStartupEffects()
{
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}

void ATiCharacter::OnDeathStarted(AActor*)
{
	DisableMovementAndCollision();
}

void ATiCharacter::OnDeathFinished(AActor*)
{
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::DestroyDueToDeath);
}

void ATiCharacter::DisableMovementAndCollision()
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

void ATiCharacter::DestroyDueToDeath()
{
	K2_OnDeathFinished();

	UninitAndDestroy();
}

void ATiCharacter::UninitAndDestroy()
{

	DetachFromControllerPendingDestroy();
	SetLifeSpan(0.1f);
	
	//SetActorHiddenInGame(true);
}

void ATiCharacter::RemoveCharacterAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	// Remove any abilities added from a previous call. This checks to make sure the ability is in the startup 'CharacterAbilities' array.
	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	// Do in two passes so the removal happens after we have the full list
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}
}

UAbilitySystemComponent* ATiCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

