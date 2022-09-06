// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DiaryEntries/TiCategoryEntry.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/TiCategoryData.h"

void UTiCategoryEntry::NativeConstruct()
{
	Super::NativeConstruct();

	MainButton->OnClicked.AddUniqueDynamic(this, &UTiCategoryEntry::OnButtonClicked);
}

void UTiCategoryEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	FCategoryData Data = Cast<UTiCategoryData>(ListItemObject)->Data;

	Category = Data.Category;

	OnClicked.BindUFunction(Data.Parent.Get(), "OnCategoryChanged");

	FText Text = UEnum::GetDisplayValueAsText(Data.Category);

	CategoryText->SetText(Text);
}

void UTiCategoryEntry::OnButtonClicked()
{
	OnClicked.Execute(Category);
}
