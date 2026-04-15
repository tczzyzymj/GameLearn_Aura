// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/Controller/AuraWidgetController.h"
#include "MainPanelWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaPointChangedSignature, float, InNewValue);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UMainPanelWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthPointChangedSignature OnHealthPointChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthPointChangedSignature OnMaxHealthPointChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaPointChangedSignature OnManaPointChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaPointChangedSignature OnMaxManaPointChanged;

protected:
	void HealthPointChanged(const FOnAttributeChangeData& InData) const;

	void MaxHealthPointChanged(const FOnAttributeChangeData& InData) const;
	
	void ManaPointChanged(const FOnAttributeChangeData& InData) const;
	
	void MaxManaPointChanged(const FOnAttributeChangeData& InData) const;
};
