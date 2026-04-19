// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/Controller/AuraWidgetController.h"
#include "MainPanelWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FUIWidgetDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MessageTexture;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaPointChangedSignature, float, InNewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetSignature, FUIWidgetDataRow, DataRow);

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
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMessageWidgetSignature OnMessageWidget;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GAS|Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
};
