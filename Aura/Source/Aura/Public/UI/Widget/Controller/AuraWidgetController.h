// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraGameDefine.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams()
	{
	}

	FWidgetControllerParams(
		APlayerController*       InPlayerController,
		APlayerState*            InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent,
		UAttributeSet*           InAttributeSet
	) : PlayerController(InPlayerController),
	    PlayerState(InPlayerState),
	    AbilitySystemComponent(InAbilitySystemComponent),
	    AttributeSet(InAttributeSet)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};

USTRUCT(BlueprintType)
struct FAuraAttributeChangeData
{
	GENERATED_USTRUCT_BODY()
	FAuraAttributeChangeData()
	{
	}

	FAuraAttributeChangeData(
		const FGameplayAttribute& InAttribute,
		float                     InOldValue,
		float                     InNewValue,
		EAuraAttributeTypes       InAttributeType
	)
	{
		Attribute     = InAttribute;
		NewValue      = InOldValue;
		OldValue      = InNewValue;
		AttributeType = InAttributeType;
	}

	FAuraAttributeChangeData(const FOnAttributeChangeData& InAttributeChangeData, EAuraAttributeTypes InAttributeType)
	{
		Attribute     = InAttributeChangeData.Attribute;
		NewValue      = InAttributeChangeData.NewValue;
		OldValue      = InAttributeChangeData.OldValue;
		AttributeType = InAttributeType;
	}

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttribute Attribute;

	UPROPERTY(BlueprintReadOnly)
	float NewValue = 0;

	UPROPERTY(BlueprintReadOnly)
	float OldValue = 0;

	UPROPERTY(BlueprintReadOnly)
	EAuraAttributeTypes AttributeType = EAuraAttributeTypes::None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, const FAuraAttributeChangeData&, InData);

/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& InParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	UFUNCTION(BlueprintCallable)
	virtual void RemoveBindDelegate(UUserWidget* InUserWidget);

	virtual void BindCallbacksToDependencies();

protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	TSoftObjectPtr<UUserWidget> BindWidget;
};
