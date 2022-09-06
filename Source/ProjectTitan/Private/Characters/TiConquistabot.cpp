// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TiConquistabot.h"

#include "Diary/TiDiaryComponent.h"

ATiConquistabot::ATiConquistabot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DiaryComponent = CreateDefaultSubobject<UTiDiaryComponent>("DiaryComponent");
}
