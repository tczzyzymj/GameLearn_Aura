// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/Controller/AuraWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UAttributeMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;

	virtual void BroadcastInitialValues() override;
	
	virtual void RemoveBindDelegate(UUserWidget* InUserWidget) override;

	UPROPERTY(BlueprintAssignable, Category = "Aura | Widget | Controller")
	FOnAttributeChangedSignature OnAttributeChangedCallback;
};
