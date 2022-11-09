// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GiltTabListWidgetBase.h"
#include "UI/Foundation/GiltButtonBase.h"
#include "GiltTabButtonBase.generated.h"

class UCommonLazyImage;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class PROJECTTITAN_API UGiltTabButtonBase : public UGiltButtonBase, public ITiTabButtonInterface
{
	GENERATED_BODY()

public:

	void SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject);
	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FGiltTabDescriptor& TabLabelInfo) override;

private:

	UPROPERTY(meta = (BindWidgetOptional))
	UCommonLazyImage* LazyImage_Icon;
};
