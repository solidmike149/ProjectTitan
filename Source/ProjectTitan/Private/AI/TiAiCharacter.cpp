// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/TiAiCharacter.h"

#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ATiAiCharacter::ATiAiCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AbilitySystemComponent = CreateDefaultSubobject<UTiAbilitySystemComponent>("AbilitySystemComponent");

	TargetWidget = CreateDefaultSubobject<UWidgetComponent>("TargetWidget");
	TargetWidget->SetupAttachment(GetMesh());
}

void ATiAiCharacter::BeginPlay()
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

void ATiAiCharacter::AddCharacterAbilities()
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

void ATiAiCharacter::InitializeAttributes()
{
	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void ATiAiCharacter::AddStartupEffects()
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



void ATiAiCharacter::Tracking(float InterpSpeed)
{
	FRotator TargetRotation = FRotationMatrix::MakeFromX(Player->GetActorLocation() - GetActorLocation()).Rotator();
	
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation,
											GetWorld()->GetDeltaSeconds(), InterpSpeed);
	SetActorRotation(NewRotation);
}

UAbilitySystemComponent* ATiAiCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
