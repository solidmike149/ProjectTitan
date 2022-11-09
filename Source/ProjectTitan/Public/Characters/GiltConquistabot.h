// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TiCharacter.h"
#include "GiltConquistabot.generated.h"

class UTiPlayerSet;
class USpringArmComponent;
class UCameraComponent;
class UTiDiaryComponent;

UCLASS(Abstract)
class PROJECTTITAN_API AGiltConquistabot : public ATiCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTiDiaryComponent* DiaryComponent;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* CameraComp;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY()
	UTiPlayerSet* PlayerAttributeSet;

	void MoveForward(float Value);

	void MoveRight(float Value);

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxStamina() const;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> Targets;

	UPROPERTY(BlueprintReadWrite)
	AActor* CurrentTarget;

	UPROPERTY(BlueprintReadWrite)
	bool bIsLocking;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void BindASCInput();

	AGiltConquistabot(const FObjectInitializer& ObjectInitializer);
	
};
