// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"

/**
 * when you modify this, please note that this information can be saved with instances
 * also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list
 **/

// Trace against Actors/Components which provide interactions.
#define Gilt_TraceChannel_Interaction					ECC_GameTraceChannel1
