// Copyright NineForce Entertainment

#include "UI/Widget/Controller/AttributeMenuWidgetController.h"

#include "AbilitySystem/Data/AuraAttributeInfoDataAsset.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetHealthPointAttribute()).AddLambda(
	// 	[this](const FOnAttributeChangeData& Attribute)
	// 	{
	// 		OnHealthPointChanged.Broadcast(Attribute.NewValue);
	// 	}
	// );

	
	//UAuraAttributeInfoDataAsset _A;
	//_A.FindAttributeInfoDataByTag()
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
}
