// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/GiltGameState.h"

#include "GameModes/GiltExperienceManagerComponent.h"


AGiltGameState::AGiltGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	ExperienceManagerComponent = CreateDefaultSubobject<UGiltExperienceManagerComponent>("ExperienceManagerComponent");
}
