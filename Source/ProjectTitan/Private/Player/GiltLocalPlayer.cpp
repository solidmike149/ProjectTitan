// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GiltLocalPlayer.h"

#include "AudioMixerBlueprintLibrary.h"
#include "Settings/GiltSettingsLocal.h"

UGiltLocalPlayer::UGiltLocalPlayer()
{
}

void UGiltLocalPlayer::PostInitProperties()
{
	Super::PostInitProperties();

	if (UGiltSettingsLocal* LocalSettings = GetLocalSettings())
	{
		LocalSettings->OnAudioOutputDeviceChanged.AddUObject(this, &UGiltLocalPlayer::OnAudioOutputDeviceChanged);
	}
}

UGiltSettingsLocal* UGiltLocalPlayer::GetLocalSettings() const
{
	return UGiltSettingsLocal::Get();
}

void UGiltLocalPlayer::OnAudioOutputDeviceChanged(const FString& InAudioOutputDeviceId)
{
	FOnCompletedDeviceSwap DevicesSwappedCallback;
	DevicesSwappedCallback.BindUFunction(this, FName("OnCompletedAudioDeviceSwap"));
	UAudioMixerBlueprintLibrary::SwapAudioOutputDevice(GetWorld(), InAudioOutputDeviceId, DevicesSwappedCallback);
}

void UGiltLocalPlayer::OnCompletedAudioDeviceSwap(const FSwapAudioOutputResult& SwapResult)
{
	if (SwapResult.Result == ESwapAudioOutputDeviceResultState::Failure)
	{
	}
}