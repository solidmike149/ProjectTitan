// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ControllerComponent.h"
#include "GiltIndicatorManagerComponent.generated.h"

class UGiltIndicatorDescriptor;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTTITAN_API UGiltIndicatorManagerComponent : public UControllerComponent
{
	GENERATED_BODY()

public:
	UGiltIndicatorManagerComponent(const FObjectInitializer& ObjectInitializer);

	static UGiltIndicatorManagerComponent* GetComponent(AController* Controller);

	UFUNCTION(BlueprintCallable, Category = Indicator)
	void AddIndicator(UGiltIndicatorDescriptor* IndicatorDescriptor);
	
	UFUNCTION(BlueprintCallable, Category = Indicator)
	void RemoveIndicator(UGiltIndicatorDescriptor* IndicatorDescriptor);

	DECLARE_EVENT_OneParam(UGiltIndicatorManagerComponent, FIndicatorEvent, UGiltIndicatorDescriptor* Descriptor)
	FIndicatorEvent OnIndicatorAdded;
	FIndicatorEvent OnIndicatorRemoved;

	const TArray<UGiltIndicatorDescriptor*>& GetIndicators() const { return Indicators; }

private:
	UPROPERTY()
	TArray<TObjectPtr<UGiltIndicatorDescriptor>> Indicators;
};
