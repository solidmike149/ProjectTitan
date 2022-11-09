// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DiaryEntries/TiIndexEntry.h"

#include "CommonButtonBase.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/TiIndexData.h"

void UTiIndexEntry::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddDynamic(this, &UTiIndexEntry::OnButtonClicked);
}

void UTiIndexEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	FIndexData Data = Cast<UTiIndexData>(ListItemObject)->Data;

	Id = Data.Id;

	OnClicked.BindUFunction(Data.Parent.Get(), "OnIndexSelected");
	
	IndexText->SetText(Data.Title);
}

void UTiIndexEntry::OnButtonClicked()
{
	OnClicked.ExecuteIfBound(Id);
}
