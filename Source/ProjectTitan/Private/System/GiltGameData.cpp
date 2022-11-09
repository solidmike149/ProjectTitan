// Fill out your copyright notice in the Description page of Project Settings.


#include "System/GiltGameData.h"

#include "System/GiltAssetManager.h"


UGiltGameData::UGiltGameData()
{
}

const UGiltGameData& UGiltGameData::Get()
{
	return UGiltAssetManager::Get().GetGameData();
}