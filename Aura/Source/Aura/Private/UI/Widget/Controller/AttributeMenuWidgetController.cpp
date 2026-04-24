// Copyright NineForce Entertainment

#include "UI/Widget/Controller/AttributeMenuWidgetController.h"

#include "AuraGameDefine.h"
#include "AbilitySystem/Data/AuraAttributeInfoDataAsset.h"
#include "Blueprint/UserWidget.h"
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
				OnAttributeChangedCallback.Broadcast(NewData);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AbilitySystemComponent);
	check(AttributeSet);
	auto TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	for (int Index = 1; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		auto TargetEnum      = static_cast<EAuraAttributeTypes>(TargetSEnum->GetValueByIndex(Index));
		auto TargetAttribute = UAuraBlueprintFunctionLibrary::GetGameplayAttributeByEnum(TargetEnum);
		checkf(
			TargetAttribute.IsValid(),
			TEXT("枚举：%s,在 AuraAttributeSet 里面没有成员变量，请检查"),
			*TargetSEnum->GetNameByIndex(Index).ToString()
		);
		auto TargetData = TargetAttribute.GetUProperty()->ContainerPtrToValuePtr<FGameplayAttributeData>(AttributeSet);
		auto CurValue = TargetData->GetCurrentValue();
		FAuraAttributeChangeData NewData(TargetAttribute, CurValue, CurValue, TargetEnum);
		OnAttributeChangedCallback.Broadcast(NewData);
	}
}

void UAttributeMenuWidgetController::RemoveBindDelegate(UUserWidget* InUserWidget)
{
	Super::RemoveBindDelegate(InUserWidget);

	OnAttributeChangedCallback.RemoveAll(InUserWidget);
}
