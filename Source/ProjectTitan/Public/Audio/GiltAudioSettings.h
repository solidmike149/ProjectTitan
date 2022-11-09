// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GiltAudioSettings.generated.h"


USTRUCT()
struct PROJECTTITAN_API FGiltSubmixEffectChainMap
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "SoundSubmix"))
	TSoftObjectPtr<USoundSubmix> Submix = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "SoundEffectSubmixPreset"))
	TArray<TSoftObjectPtr<USoundEffectSubmixPreset>> SubmixEffectChain;

};
/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "GiltAudioSettings"))
class PROJECTTITAN_API UGiltAudioSettings : public UDeveloperSettings
{
	GENERATED_BODY()

	public:

	/** The Default Base Control Bus Mix */
	UPROPERTY(config, EditAnywhere, Category = MixSettings, meta = (AllowedClasses = "SoundControlBusMix"))
	FSoftObjectPath DefaultControlBusMix;

	/** The Loading Screen Control Bus Mix - Called during loading screens to cover background audio events */
	UPROPERTY(config, EditAnywhere, Category = MixSettings, meta = (AllowedClasses = "SoundControlBusMix"))
	FSoftObjectPath LoadingScreenControlBusMix;

	/** The Default Base Control Bus Mix */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBusMix"))
	FSoftObjectPath UserSettingsControlBusMix;

	/** Control Bus assigned to the Overall sound volume setting */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBus"))
	FSoftObjectPath OverallVolumeControlBus;

	/** Control Bus assigned to the Music sound volume setting */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBus"))
	FSoftObjectPath MusicVolumeControlBus;

	/** Control Bus assigned to the SoundFX sound volume setting */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBus"))
	FSoftObjectPath SoundFXVolumeControlBus;

	/** Control Bus assigned to the Dialogue sound volume setting */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBus"))
	FSoftObjectPath DialogueVolumeControlBus;

	/** Control Bus assigned to the VoiceChat sound volume setting */
	UPROPERTY(config, EditAnywhere, Category = UserMixSettings, meta = (AllowedClasses = "SoundControlBus"))
	FSoftObjectPath VoiceChatVolumeControlBus;

	/** Submix Processing Chains to achieve high dynamic range audio output */
	UPROPERTY(config, EditAnywhere, Category = EffectSettings)
	TArray<FGiltSubmixEffectChainMap> HDRAudioSubmixEffectChain;
	
	/** Submix Processing Chains to achieve low dynamic range audio output */
	UPROPERTY(config, EditAnywhere, Category = EffectSettings)
	TArray<FGiltSubmixEffectChainMap> LDRAudioSubmixEffectChain;
};
