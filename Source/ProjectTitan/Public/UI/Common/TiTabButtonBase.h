// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TiTabListWidgetBase.h"
#include "UI/Common/TiButtonBase.h"
#include "TiTabButtonBase.generated.h"

class UCommonLazyImage;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, meta = (DisableNativeTick))
class PROJECTTITAN_API UTiTabButtonBase : public UTiButtonBase, public ITiTabButtonInterface
{
	GENERATED_BODY()


public:

	void SetIconFromLazyObject(TSoftObjectPtr<UObject> LazyObject);
	void SetIconBrush(const FSlateBrush& Brush);

protected:

	UFUNCTION()
	virtual void SetTabLabelInfo_Implementation(const FTiTabDescriptor& TabLabelInfo) override;

private:

	UPROPERTY(meta = (BindWidgetOptional))
	UCommonLazyImage* LazyImage_Icon;
};
