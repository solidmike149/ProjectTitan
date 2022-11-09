// Fill out your copyright notice in the Description page of Project Settings.


#include "Diary/TiDiaryComponent.h"

#include "Blueprint/WidgetBlueprintLibrary.h"


UTiDiaryComponent::UTiDiaryComponent()
{

}

void UTiDiaryComponent::AddDiaryEntry(FName EntryId)
{
	if (DiaryTable == nullptr)
	{
		FString StringDebug = FString::Printf(TEXT("Set DataTable On Diary Component"));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, StringDebug);
		return;
	}
	
	FString ContextString = "SearchForEntry";
	FDiaryEntry* Entry = DiaryTable->FindRow<FDiaryEntry>(EntryId, ContextString, true);

	if (Entry)
	{
		Diary.Add(EntryId, *Entry);

		if(!bIsInDebugMode)
		{GetOwner()->DisableInput(GetWorld()->GetFirstPlayerController());
            		
			OnDiaryEntryAdded.Broadcast(this, *Entry);
		}
		
		if (!UnlockedCategories.Contains(Entry->CategoryKey))
		{
			UnlockedCategories.Add(Entry->CategoryKey);
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


void UTiDiaryComponent::GetEntryDataByCategory(const FString& Category, TArray<FIndexData>& OutData) const
{
	TArray<FDiaryEntry> Entries;
	
	Diary.GenerateValueArray(Entries);

	for (auto& DiaryEntry : Diary)
	{
		if (DiaryEntry.Value.CategoryKey == Category)
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


TArray<FString> UTiDiaryComponent::GetUnlockedCategories() const
{
	return UnlockedCategories;
}
