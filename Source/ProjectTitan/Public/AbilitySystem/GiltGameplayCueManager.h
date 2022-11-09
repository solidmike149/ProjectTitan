// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "GiltGameplayCueManager.generated.h"

/**
 * UGiltGameplayCueManager
 *
 * Game-specific manager for gameplay cues
 */
UCLASS()
class UGiltGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()

	public:
	UGiltGameplayCueManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static UGiltGameplayCueManager* Get();

	//~UGameplayCueManager interface
	virtual void OnCreated() override;
	virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const override;
	virtual bool ShouldSyncLoadMissingGameplayCues() const override;
	virtual bool ShouldAsyncLoadMissingGameplayCues() const override;
	//~End of UGameplayCueManager interface

	static void DumpGameplayCues(const TArray<FString>& Args);

	// When delay loading cues, this will load the cues that must be always loaded anyway
	void LoadAlwaysLoadedCues();

	// Updates the bundles for the singular gameplay cue primary asset
	void RefreshGameplayCuePrimaryAsset();

private:
	void OnGameplayTagLoaded(const FGameplayTag& Tag);
	void HandlePostGarbageCollect();
	void ProcessLoadedTags();
	void ProcessTagToPreload(const FGameplayTag& Tag, UObject* OwningObject);
	void OnPreloadCueComplete(FSoftObjectPath Path, TWeakObjectPtr<UObject> OwningObject, bool bAlwaysLoadedCue);
	void RegisterPreloadedCue(UClass* LoadedGameplayCueClass, UObject* OwningObject);
	void HandlePostLoadMap(UWorld* NewWorld);
	void UpdateDelayLoadDelegateListeners();
	bool ShouldDelayLoadGameplayCues() const;
	
	struct FLoadedGameplayTagToProcessData
	{
		FGameplayTag Tag;
		TWeakObjectPtr<UObject> WeakOwner;

		FLoadedGameplayTagToProcessData() {}
		FLoadedGameplayTagToProcessData(const FGameplayTag& InTag, const TWeakObjectPtr<UObject>& InWeakOwner) : Tag(InTag), WeakOwner(InWeakOwner) {}
	};
	
	// Cues that were preloaded on the client due to being referenced by content
	UPROPERTY(transient)
	TSet<UClass*> PreloadedCues;
	TMap<FObjectKey, TSet<FObjectKey>> PreloadedCueReferencers;

	// Cues that were preloaded on the client and will always be loaded (code referenced or explicitly always loaded)
	UPROPERTY(transient)
	TSet<UClass*> AlwaysLoadedCues;

	TArray<FLoadedGameplayTagToProcessData> LoadedGameplayTagsToProcess;
	FCriticalSection LoadedGameplayTagsToProcessCS;
	bool bProcessLoadedTagsAfterGC = false;
};
