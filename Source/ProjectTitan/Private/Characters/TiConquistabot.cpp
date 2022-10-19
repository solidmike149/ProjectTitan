// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TiConquistabot.h"

#include "AbilitySystem/TiAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TiPlayerSet.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "Diary/TiDiaryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectTitan/ProjectTitan.h"


ATiConquistabot::ATiConquistabot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
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

	PlayerAttributeSet = CreateDefaultSubobject<UTiPlayerSet>("PlayerSet");
	DiaryComponent = CreateDefaultSubobject<UTiDiaryComponent>("DiaryComponent");
}


void ATiConquistabot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATiConquistabot::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATiConquistabot::MoveRight);

	BindASCInput();

	//PlayerInputComponent->BindAction("Shoot",IE_Pressed, this, &ATiCharacter::ShootPressed);
	//PlayerInputComponent->BindAction("Shoot",IE_Released, this, &ATiCharacter::ShootReleased);
	//PlayerInputComponent->BindAction("Roll",IE_Pressed, this, &ATiCharacter::Roll);
	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATiCharacter::SprintStart);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATiCharacter::SprintStop);
}


void ATiConquistabot::BindASCInput()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("ETiAbilityInputID"), static_cast<int32>(ETiAbilityInputID::Confirm), static_cast<int32>(ETiAbilityInputID::Cancel)));
	}
}


void ATiConquistabot::MoveForward(float Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw - 45, 0);

	// get forward vector
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}


void ATiConquistabot::MoveRight(float Value)
{
	// find out which way is right
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw - 45, 0);
	
	// get right vector 
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// add movement in that direction
	AddMovementInput(Direction, Value);
}


float ATiConquistabot::GetMaxStamina() const
{
	if (PlayerAttributeSet)
	{
		return PlayerAttributeSet->GetMaxStamina();
	}
	return 0.0f;
}
