// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioMixerBlueprintLibrary.h"
#include "CommonLocalPlayer.h"
#include "GiltLocalPlayer.generated.h"

class UGiltSettingsLocal;
/**
 * 
 */
UCLASS()
class PROJECTTITAN_API UGiltLocalPlayer : public UCommonLocalPlayer
{
	GENERATED_BODY()

public:

	UGiltLocalPlayer();

	//~UObject interface
	virtual void PostInitProperties() override;
	//~End of UObject interface
	
	UFUNCTION()
	UGiltSettingsLocal* GetLocalSettings() const;

protected:
	void OnAudioOutputDeviceChanged(const FString& InAudioOutputDeviceId);
	
	UFUNCTION()
	void OnCompletedAudioDeviceSwap(const FSwapAudioOutputResult& SwapResult);
};
