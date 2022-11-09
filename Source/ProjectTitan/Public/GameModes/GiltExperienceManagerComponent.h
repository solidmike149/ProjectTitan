// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFeaturePluginOperationResult.h"
#include "LoadingProcessInterface.h"
#include "Components/GameStateComponent.h"
#include "GiltExperienceManagerComponent.generated.h"

class UGiltExperienceDefinition;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGiltExperienceLoaded, const UGiltExperienceDefinition* /*Experience*/);


enum class EGiltExperienceLoadState
{
	Unloaded,
	Loading,
	LoadingGameFeatures,
	LoadingChaosTestingDelay,
	ExecutingActions,
	Loaded,
	Deactivating
};

UCLASS()
class PROJECTTITAN_API UGiltExperienceManagerComponent final : public UGameStateComponent, public ILoadingProcessInterface
{
	GENERATED_BODY()

public:

	//~UActorComponent interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

	//~ILoadingProcessInterface interface
	virtual bool ShouldShowLoadingScreen(FString& OutReason) const override;
	//~End of ILoadingProcessInterface

#if WITH_SERVER_CODE
	void ServerSetCurrentExperience(FPrimaryAssetId ExperienceId);
#endif

	// Ensures the delegate is called once the experience has been loaded,
	// before others are called.
	// However, if the experience has already loaded, calls the delegate immediately.
	void CallOrRegister_OnExperienceLoaded_HighPriority(FOnGiltExperienceLoaded::FDelegate&& Delegate);

	// Ensures the delegate is called once the experience has been loaded
	// If the experience has already loaded, calls the delegate immediately
	void CallOrRegister_OnExperienceLoaded(FOnGiltExperienceLoaded::FDelegate&& Delegate);

	// Ensures the delegate is called once the experience has been loaded
	// If the experience has already loaded, calls the delegate immediately
	void CallOrRegister_OnExperienceLoaded_LowPriority(FOnGiltExperienceLoaded::FDelegate&& Delegate);

	// This returns the current experience if it is fully loaded, asserting otherwise
	// (i.e., if you called it too soon)
	const UGiltExperienceDefinition* GetCurrentExperienceChecked() const;

	// Returns true if the experience is fully loaded
	bool IsExperienceLoaded() const;

private:
	UFUNCTION()
	void OnRep_CurrentExperience();

	void StartExperienceLoad();
	void OnExperienceLoadComplete();
	void OnGameFeaturePluginLoadComplete(const UE::GameFeatures::FResult& Result);
	void OnExperienceFullLoadCompleted();

	void OnActionDeactivationCompleted();
	void OnAllActionsDeactivated();
	
	UPROPERTY(ReplicatedUsing=OnRep_CurrentExperience)
	const UGiltExperienceDefinition* CurrentExperience;

	EGiltExperienceLoadState LoadState = EGiltExperienceLoadState::Unloaded;

	int32 NumGameFeaturePluginsLoading = 0;
	TArray<FString> GameFeaturePluginURLs;

	int32 NumObservedPausers = 0;
	int32 NumExpectedPausers = 0;

	/**
	 * Delegate called when the experience has finished loading just before others
	 * (e.g., subsystems that set up for regular gameplay)
	 */
	FOnGiltExperienceLoaded OnExperienceLoaded_HighPriority;

	/** Delegate called when the experience has finished loading */
	FOnGiltExperienceLoaded OnExperienceLoaded;

	/** Delegate called when the experience has finished loading */
	FOnGiltExperienceLoaded OnExperienceLoaded_LowPriority;
};
