// Copyright NineForce Entertainment

#include "Util/Blueprint/AuraBlueprintFunctionLibrary.h"

#include "AuraEnumToGASManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/Controller/AuraWidgetController.h"

UAuraWidgetController* UAuraBlueprintFunctionLibrary::GetWidgetController(const UObject* WorldContextObject)
{
	APlayerController* TargetPC = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
	if (TargetPC == nullptr)
	{
		return nullptr;
	}
	auto TargetPlayerState = TargetPC->GetPlayerState<AAuraPlayerState>();
	if (TargetPlayerState == nullptr)
	{
		return nullptr;
	}

	auto TargetASC = TargetPlayerState->GetAbilitySystemComponent();
	auto TargetAS  = TargetPlayerState->GetAttributeSet();

	if (auto AuraHUD = Cast<AAuraHUD>(TargetPC->GetHUD()))
	{
		FWidgetControllerParams Params = FWidgetControllerParams(TargetPC, TargetPlayerState, TargetASC, TargetAS);
		return AuraHUD->GetMainPanelWidgetController(Params);
	}

	return nullptr;
}

int32 UAuraBlueprintFunctionLibrary::GetEAttributeTypeValueByIndex(int32 InIndex)
{
	auto TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	return TargetSEnum->GetValueByIndex(InIndex);
}

EAuraAttributeTypes UAuraBlueprintFunctionLibrary::GetEAttributeTypeByIndex(int32 InIndex)
{
	auto TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	auto TargetValue = TargetSEnum->GetValueByIndex(InIndex);
	if (TargetValue == INDEX_NONE)
	{
		return EAuraAttributeTypes::None;
	}

	return static_cast<EAuraAttributeTypes>(TargetValue);
}

FGameplayTag UAuraBlueprintFunctionLibrary::GetGameplayTagByEnum(EAuraAttributeTypes InType)
{
	return FAuraEnumToGASManager::GetGameplayTagByEnum(InType);
}

FGameplayAttribute UAuraBlueprintFunctionLibrary::GetGameplayAttributeByEnum(EAuraAttributeTypes InType)
{
	return FAuraEnumToGASManager::GetGameplayAttributeByEnum(InType);
}
