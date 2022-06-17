// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "TiAsyncTaskAttributeChanged.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue,
                                               float, OldValue);

/**
 * Blueprint node to automatically register a listener for all attribute changes in an AbilitySystemComponent.
 * Useful to use in UI.
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class PROJECTTITAN_API UTiAsyncTaskAttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;
	
	// Listens for an attribute changing.
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UTiAsyncTaskAttributeChanged* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

	// Listens for an attribute changing.
	// Version that takes in an array of Attributes. Check the Attribute output for which Attribute changed.
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UTiAsyncTaskAttributeChanged* ListenForAttributesChange(UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	// You must call this function manually when you want the AsyncTask to end.
	// For UMG Widgets, you would call it in the Widget's Destruct event.
	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
