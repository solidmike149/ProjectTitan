// Fill out your copyright notice in the Description page of Project Settings.


#include "Diary/TiDiaryComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"


UTiDiaryComponent::UTiDiaryComponent()
{

}




void UTiDiaryComponent::AddDiaryEntry(FName EntryId)
{
	if(DiaryTable == nullptr)
	{
		FString StringDebug = FString::Printf(TEXT("Set DataTable On Diary Component"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, StringDebug);
		return;
	}
	
	FString ContextString = "SearchForEntry";
	FDiaryEntry* Entry = DiaryTable->FindRow<FDiaryEntry>(EntryId, ContextString, true);

	if (Entry)
	{
		// TODO
		//GetOwner()->DisableInput(GetWorld()->GetFirstPlayerController());
		Diary.Add(EntryId, *Entry);

		// TODO
		//OnDiaryEntryAdded.Broadcast(this, *Entry);
		
		if (!UnlockedCategories.Contains(Entry->Category))
		{
			UnlockedCategories.Add(Entry->Category);
		}
	}
	
	else
	{
		FString StringDebug = FString::Printf(TEXT("Check Id On Interactable Actor"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, StringDebug);
	}
}


void UTiDiaryComponent::ClosePopUp()
{
	GetOwner()->EnableInput(GetWorld()->GetFirstPlayerController());
}


void UTiDiaryComponent::GetEntryDataByCategory(EEntryCategory Category, TArray<FIndexData>& OutData) const
{
	TArray<FDiaryEntry> Entries;
	
	Diary.GenerateValueArray(Entries);

	for (auto& DiaryEntry : Diary)
	{
		if (DiaryEntry.Value.Category == Category)
		{
			FIndexData NewIndex = FIndexData(nullptr, DiaryEntry.Key, DiaryEntry.Value.Title);
			OutData.Add(NewIndex);
		}
	}
}

bool UTiDiaryComponent::GetEntryById(FName Id, FDiaryEntry& Data) const
{
	if (Diary.Find(Id))
	{
		Data = *Diary.Find(Id);
		return true;
	}
	
	return false;
}

TArray<FText> UTiDiaryComponent::GetEntryTitlesByCategory(EEntryCategory Category) const
{
	TArray<FDiaryEntry> Entries;

	Diary.GenerateValueArray(Entries);

	TArray<FText> Titles;

	for (FDiaryEntry& Entry : Entries)
	{
		if (Entry.Category == Category)
		{
			Titles.Add(Entry.Title);
		}
	}

	return Titles;
}


TArray<EEntryCategory> UTiDiaryComponent::GetUnlockedCategories() const
{
	return UnlockedCategories;
}
