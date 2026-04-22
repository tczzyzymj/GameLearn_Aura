// Copyright NineForce Entertainment

#include "UI/Widget/Controller/AttributeMenuWidgetController.h"

#include "AuraGameDefine.h"
#include "AbilitySystem/Data/AuraAttributeInfoDataAsset.h"
#include "Util/Blueprint/AuraBlueprintFunctionLibrary.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AbilitySystemComponent);
	auto TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	for (int Index = 1; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		auto TargetEnum      = static_cast<EAuraAttributeTypes>(TargetSEnum->GetValueByIndex(Index));
		auto TargetAttribute = UAuraBlueprintFunctionLibrary::GetGameplayAttributeByEnum(TargetEnum);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute).AddLambda(
			[this](const FOnAttributeChangeData& InData)
			{
				FAuraAttributeChangeData NewData = FAuraAttributeChangeData(InData);
				if (NewData.Attribute == InData.Attribute)
				{
					
				}
				OnAttributeChangedCallback.Broadcast(NewData);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
}
