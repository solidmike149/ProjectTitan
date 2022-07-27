// Fill out your copyright notice in the Description page of Project Settings.


#include "TiCharacter.h"

#include "TiCharacterMovementComponent.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "AbilitySystem/TiGameplayAbility.h"
#include "AbilitySystem/AttributeSets/TiHealthSet.h"
#include "AbilitySystem/AttributeSets/TiPlayerSet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ATiCharacter::ATiCharacter(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UTiCharacterMovementComponent>(CharacterMovementComponentName))
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

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-30.f, -45.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComp->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Widget = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	Widget->SetupAttachment(GetCapsuleComponent());
	Widget->SetUsingAbsoluteRotation(true);

	AbilitySystemComponent = CreateDefaultSubobject<UTiAbilitySystemComponent>("ActionComponent");

	HealthAttributeSet = CreateDefaultSubobject<UTiHealthSet>("HealthSet");

	PlayerAttributeSet = CreateDefaultSubobject<UTiPlayerSet>("PlayerSet");
}

void ATiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATiCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATiCharacter::MoveRight);

	//PlayerInputComponent->BindAction("Shoot",IE_Pressed, this, &ATiCharacter::ShootPressed);
	//PlayerInputComponent->BindAction("Shoot",IE_Released, this, &ATiCharacter::ShootReleased);
	
	//PlayerInputComponent->BindAction("Roll",IE_Pressed, this, &ATiCharacter::Roll);

	BindASCInput();

	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATiCharacter::SprintStart);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATiCharacter::SprintStop);
}

void ATiCharacter::BindASCInput()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("ETiAbilityInputID"), static_cast<int32>(ETiAbilityInputID::Confirm), static_cast<int32>(ETiAbilityInputID::Cancel)));
	}
}

void ATiCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthAttributeSet->OnOutOfHealth.AddUObject(this, &ATiCharacter::OnDeathStarted);
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


void ATiCharacter::MoveForward(float Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw - 45, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}

void ATiCharacter::MoveRight(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw - 45, 0);
	
	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}


void ATiCharacter::Roll()
{
	if(GetVelocity().Size() > 0.1f)
	{
		
	}
	else
	{
		
	}
}


void ATiCharacter::OnDeathStarted(AActor* EffectInstigator, AActor* EffectCauser, const FGameplayEffectSpec& EffectSpec, float EffectMagnitude)
{
	DisableMovementAndCollision();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->CancelAllAbilities();
	}
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

	UTiCharacterMovementComponent* MoveComp = CastChecked<UTiCharacterMovementComponent>(GetCharacterMovement());
	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();
}


void ATiCharacter::DestroyDueToDeath()
{
	K2_OnDeathFinished();
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

	// Can run on Server and Client
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

float ATiCharacter::GetMoveSpeed() const
{
	if (PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetSpeed();
	}
	return 0.0f;
}

float ATiCharacter::GetMaxStamina() const
{
	if (PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}

float ATiCharacter::GetHealth() const
{
	if (HealthAttributeSet)
	{
		return HealthAttributeSet->GetHealth();
	}
	return 0.0f;
}

bool ATiCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}