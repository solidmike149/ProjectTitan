﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTabListWidgetBase.h"
#include "UObject/Object.h"
#include "GiltTabListWidgetBase.generated.h"

class UWidget;
class UCommonUserWidget;
class UCommonButtonBase;

USTRUCT(BlueprintType)
struct FGiltTabDescriptor
{
	GENERATED_BODY()
	
	FGiltTabDescriptor()
	: bHidden(false)
	, CreatedTabContentWidget(nullptr)
	{ }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName TabId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText TabText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush IconBrush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHidden;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCommonButtonBase> TabButtonType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCommonUserWidget> TabContentType;

	UPROPERTY(Transient)
	UWidget* CreatedTabContentWidget;
};

UINTERFACE(BlueprintType)
class UTiTabButtonInterface : public UInterface
{
	GENERATED_BODY()
};

class ITiTabButtonInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category = "Tab Button")
	void SetTabLabelInfo(const FGiltTabDescriptor& TabDescriptor);
};


UCLASS(Abstract)
class PROJECTTITAN_API UGiltTabListWidgetBase : public UCommonTabListWidgetBase
{
	GENERATED_BODY()

	public:

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
    bool GetPreregisteredTabInfo(const FName TabNameId, FGiltTabDescriptor& OutTabInfo);

    /** Helper method to get at all the preregistered tab infos */
    const TArray<FGiltTabDescriptor>& GetAllPreregisteredTabInfos() { return PreregisteredTabInfoArray; }

    // Toggles whether or not a specified tab is hidden, can only be called before the switcher is associated
    UFUNCTION(BlueprintCallable, Category = "Tab List")
    void SetTabHiddenState(FName TabNameId, bool bHidden);

    UFUNCTION(BlueprintCallable, Category = "Tab List")
    bool RegisterDynamicTab(const FGiltTabDescriptor& TabDescriptor);

    UFUNCTION(BlueprintCallable, Category = "Tab List")
    bool IsFirstTabActive() const;

    UFUNCTION(BlueprintCallable, Category = "Tab List")
    bool IsLastTabActive() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
    bool IsTabVisible(FName TabId);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Tab List")
    int32 GetVisibleTabCount();

    /** Delegate broadcast when a new tab is created. Allows hook ups after creation. */
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTabContentCreated, FName, TabId, UCommonUserWidget*, TabWidget);
    DECLARE_EVENT_TwoParams(ULyraTabListWidgetBase, FOnTabContentCreatedNative, FName /* TabId */, UCommonUserWidget* /* TabWidget */);

    /** Broadcasts when a new tab is created. */
    UPROPERTY(BlueprintAssignable, Category = "Tab List")
    FOnTabContentCreated OnTabContentCreated;
    FOnTabContentCreatedNative OnTabContentCreatedNative;

protected:
    // UUserWidget interface
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    // End UUserWidget

    virtual void HandlePreLinkedSwitcherChanged() override;
    virtual void HandlePostLinkedSwitcherChanged() override;

    virtual void HandleTabCreation_Implementation(FName TabId, UCommonButtonBase* TabButton) override;

private:
    void SetupTabs();

    UPROPERTY(EditAnywhere, meta=(TitleProperty="TabId"))
    TArray<FGiltTabDescriptor> PreregisteredTabInfoArray;
    
    /**
     * Stores label info for tabs that have been registered at runtime but not yet created. 
     * Elements are removed once they are created.
     */
    UPROPERTY()
    TMap<FName, FGiltTabDescriptor> PendingTabLabelInfoMap;
};
