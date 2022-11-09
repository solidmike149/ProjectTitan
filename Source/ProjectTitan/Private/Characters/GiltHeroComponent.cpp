// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GiltHeroComponent.h"

#include "EnhancedInputSubsystems.h"
#include "GiltGameplayTags.h"
#include "GiltLogChannels.h"
#include "AbilitySystem/GiltAbilitySystemComponent.h"
#include "Characters/GiltPawnData.h"
#include "Characters/GiltPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "Input/GiltInputComponent.h"
#include "Player/GiltPlayerController.h"
#include "Player/GiltPlayerState.h"
#include "Settings/GiltSettingsLocal.h"

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#endif	// WITH_EDITOR

namespace GiltHero
{
	static const float LookYawRate = 300.0f;
	static const float LookPitchRate = 165.0f;
}

const FName UGiltHeroComponent::NAME_BindInputsNow("BindInputsNow");

UGiltHeroComponent::UGiltHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bPawnHasInitialized = false;
	bReadyToBindInputs = false;
}

void UGiltHeroComponent::OnRegister()
{
	Super::OnRegister();

	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnExtComp->OnPawnReadyToInitialize_RegisterAndCall(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnPawnReadyToInitialize));
		}
	}
	else
	{
		UE_LOG(LogGilt, Error, TEXT("[UGiltHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));

#if WITH_EDITOR
		if (GIsEditor)
		{
			static const FText Message = NSLOCTEXT("GiltHeroComponent", "NotOnPawnError", "has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint. This will cause a crash if you PIE!");
			static const FName HeroMessageLogName = TEXT("GiltHeroComponent");
			
			FMessageLog(HeroMessageLogName).Error()
				->AddToken(FUObjectToken::Create(this, FText::FromString(GetNameSafe(this))))
				->AddToken(FTextToken::Create(Message));
				
			FMessageLog(HeroMessageLogName).Open();
		}
#endif
	}
}

bool UGiltHeroComponent::IsPawnComponentReadyToInitialize() const
{
	// The player state is required.
	if (!GetPlayerState<AGiltPlayerState>())
	{
		return false;
	}

	const APawn* Pawn = GetPawn<APawn>();

	// A pawn is required.
	if (!Pawn)
	{
		return false;
	}

	// If we're authority or autonomous, we need to wait for a controller with registered ownership of the player state.
	if (Pawn->GetLocalRole() != ROLE_SimulatedProxy)
	{
		AController* Controller = GetController<AController>();

		const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
												(Controller->PlayerState != nullptr) && \
												(Controller->PlayerState->GetOwner() == Controller);

		if (!bHasControllerPairedWithPS)
		{
			return false;
		}
	}
	
	const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
	const bool bIsBot = Pawn->IsBotControlled();

	if (bIsLocallyControlled && !bIsBot)
	{
		// The input component is required when locally controlled.
		if (!Pawn->InputComponent)
		{
			return false;
		}
	}

	return true;
}

void UGiltHeroComponent::OnPawnReadyToInitialize()
{
	if (!ensure(!bPawnHasInitialized))
	{
		// Don't initialize twice
		return;
	}

	APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	AGiltPlayerState* GiltPS = GetPlayerState<AGiltPlayerState>();
	check(GiltPS);

	const UGiltPawnData* PawnData = nullptr;

	if (UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		PawnData = PawnExtComp->GetPawnData<UGiltPawnData>();

		// The player state holds the persistent data for this player (state that persists across deaths and multiple pawns).
		// The ability system component and attribute sets live on the player state.
		PawnExtComp->InitializeAbilitySystem(GiltPS->GetGiltAbilitySystemComponent(), GiltPS);
	}

	if (AGiltPlayerController* GiltPC = GetController<AGiltPlayerController>())
	{
		if (Pawn->InputComponent != nullptr)
		{
			InitializePlayerInput(Pawn->InputComponent);
		}
	}

	bPawnHasInitialized = true;
}

void UGiltHeroComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGiltHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnExtComp->UninitializeAbilitySystem();
		}	
	}

	Super::EndPlay(EndPlayReason);
}

void UGiltHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UGiltPawnData* PawnData = PawnExtComp->GetPawnData<UGiltPawnData>())
		{
			if (const UGiltInputConfig* InputConfig = PawnData->InputConfig)
			{
				const FGiltGameplayTags& GameplayTags = FGiltGameplayTags::Get();
	
				// Register any default input configs with the settings so that they will be applied to the player during AddInputMappings
				for (const FMappableConfigPair& Pair : DefaultInputConfigs)
				{
					FMappableConfigPair::ActivatePair(Pair);
				}
				
				UGiltInputComponent* GiltIC = CastChecked<UGiltInputComponent>(PlayerInputComponent);
				GiltIC->AddInputMappings(InputConfig, Subsystem);
				if (UGiltSettingsLocal* LocalSettings = UGiltSettingsLocal::Get())
				{
					LocalSettings->OnInputConfigActivated.AddUObject(this, &UGiltHeroComponent::OnInputConfigActivated);
					LocalSettings->OnInputConfigDeactivated.AddUObject(this, &UGiltHeroComponent::OnInputConfigDeactivated);
				}

				TArray<uint32> BindHandles;
				GiltIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

				GiltIC->BindNativeAction(InputConfig, GameplayTags.InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, /*bLogIfNotFound=*/ false);
			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}

void UGiltHeroComponent::OnInputConfigActivated(const FLoadedMappableConfigPair& ConfigPair)
{
	if (AGiltPlayerController* GiltPC = GetController<AGiltPlayerController>())
	{
		if (APawn* Pawn = GetPawn<APawn>())
		{
			if (UGiltInputComponent* GiltIC = Cast<UGiltInputComponent>(Pawn->InputComponent))
			{
				if (const ULocalPlayer* LP = GiltPC->GetLocalPlayer())
				{
					if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
					{
						GiltIC->AddInputConfig(ConfigPair, Subsystem);	
					}	
				}
			}
		}
	}
}

void UGiltHeroComponent::OnInputConfigDeactivated(const FLoadedMappableConfigPair& ConfigPair)
{
	if (AGiltPlayerController* GiltPC = GetController<AGiltPlayerController>())
	{
		if (APawn* Pawn = GetPawn<APawn>())
		{
			if (UGiltInputComponent* GiltIC = Cast<UGiltInputComponent>(Pawn->InputComponent))
			{
				if (const ULocalPlayer* LP = GiltPC->GetLocalPlayer())
				{
					if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
					{
						GiltIC->RemoveInputConfig(ConfigPair, Subsystem);
					}
				}
			}
		}
	}
}

void UGiltHeroComponent::AddAdditionalInputConfig(const UGiltInputConfig* InputConfig)
{
	TArray<uint32> BindHandles;

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	UGiltInputComponent* GiltIC = Pawn->FindComponentByClass<UGiltInputComponent>();
	check(GiltIC);

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	if (const UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		GiltIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
	}
}

bool UGiltHeroComponent::HasPawnInitialized() const
{
	return bPawnHasInitialized;
}

bool UGiltHeroComponent::IsReadyToBindInputs() const
{
	return bReadyToBindInputs;
}

void UGiltHeroComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (const UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			if (UGiltAbilitySystemComponent* GiltASC = PawnExtComp->GetGiltAbilitySystemComponent())
			{
				GiltASC->AbilityInputTagPressed(InputTag);
			}
		}	
	}
}

void UGiltHeroComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	if (const UGiltPawnExtensionComponent* PawnExtComp = UGiltPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (UGiltAbilitySystemComponent* GiltASC = PawnExtComp->GetGiltAbilitySystemComponent())
		{
			GiltASC->AbilityInputTagReleased(InputTag);
		}
	}
}

void UGiltHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;
	
	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UGiltHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UGiltHeroComponent::Input_LookStick(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	const UWorld* World = GetWorld();
	check(World);

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X * GiltHero::LookYawRate * World->GetDeltaSeconds());
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y * GiltHero::LookPitchRate * World->GetDeltaSeconds());
	}
}

