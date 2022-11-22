// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GiltPlayerState.h"

#include "GiltLogChannels.h"
#include "AbilitySystem/GiltAbilitySet.h"
#include "AbilitySystem/GiltAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/GiltHealthSet.h"
#include "Characters/GiltPawnData.h"
#include "Characters/GiltPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "GameModes/GiltExperienceManagerComponent.h"
#include "Player/GiltPlayerController.h"

const FName AGiltPlayerState::NAME_LyraAbilityReady("GiltAbilitiesReady");

AGiltPlayerState::AGiltPlayerState(const FObjectInitializer& ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UGiltAbilitySystemComponent>(this, "AbilitySystemComponent");

	CreateDefaultSubobject<UGiltHealthSet>("HealthSet");
}

AGiltPlayerController* AGiltPlayerState::GetGiltPlayerController() const
{
	return Cast<AGiltPlayerController>(GetOwner());
}

UAbilitySystemComponent* AGiltPlayerState::GetAbilitySystemComponent() const
{
	return GetGiltAbilitySystemComponent();
}

void AGiltPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());
	
	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);
	UGiltExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<UGiltExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnGiltExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void AGiltPlayerState::OnExperienceLoaded(const UGiltExperienceDefinition* /*CurrentExperience*/)
{
	if (APawn* PossesedPawn = GetPawn())
	{
		if (UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(PossesedPawn))
		{
			if (const UGiltPawnData* NewPawnData = PawnExtComp->GetPawnData<UGiltPawnData>())
			{
				SetPawnData(NewPawnData);
			}
			else
			{
				UE_LOG(LogGilt, Error, TEXT("PlayerState was unable to set PawnData on the spawned pawn [%s]."), *GetNameSafe(PossesedPawn));
			}
		}
	}

}

void AGiltPlayerState::SetPawnData(const UGiltPawnData* InPawnData)
{
	check(InPawnData);

	if (PawnData)
	{
		UE_LOG(LogGilt, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}

	//MARK_PROPERTY_DIRTY_FROM_NAME(ThisClass, PawnData, this);
	PawnData = InPawnData;

	for (const UGiltAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, NAME_LyraAbilityReady);
}
