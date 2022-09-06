// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TiCharacter.h"
#include "TiConquistabot.generated.h"

class UTiDiaryComponent;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API ATiConquistabot : public ATiCharacter
{
	GENERATED_BODY()

	ATiConquistabot(const FObjectInitializer& ObjectInitializer);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTiDiaryComponent* DiaryComponent;
};
