// Copyright NineForce Entertainment

#include "Util/Blueprint/AuraBlueprintFunctionLibrary.h"

#include "AuraGASEnumManager.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/Controller/AuraWidgetController.h"

UAuraWidgetController* UAuraBlueprintFunctionLibrary::GetMainPanelWidgetController(const UObject* WorldContextObject)
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

UAuraWidgetController* UAuraBlueprintFunctionLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
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
		return AuraHUD->GetAttributeMenuWidgetController(Params);
	}

	return nullptr;
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
	return FAuraGASEnumManager::GetAttributeGameplayTagByEnum(InType);
}

FGameplayAttribute UAuraBlueprintFunctionLibrary::GetGameplayAttributeByEnum(EAuraAttributeTypes InType)
{
	return FAuraGASEnumManager::GetGameplayAttributeByEnum(InType);
}

float UAuraBlueprintFunctionLibrary::GetAttributeBaseValueByEnum(EAuraAttributeTypes InType, UAuraAttributeSet* InAttributeSet)
{
	if (!IsValid(InAttributeSet))
	{
		UE_LOG(LogTemp, Error, TEXT("UAuraBlueprintFunctionLibrary::GetAttributeBaseValueByEnum, but InAttributeSet==nullptr"));
		return 0;
	}
	auto TargetAttribute = GetGameplayAttributeByEnum(InType);
	if (!TargetAttribute.IsValid())
	{
		return INDEX_NONE;
	}

	FGameplayAttributeData* TargetData = TargetAttribute.GetUProperty()->ContainerPtrToValuePtr<FGameplayAttributeData>(
		InAttributeSet
	);

	if (TargetData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UAuraBlueprintFunctionLibrary::GetAttributeBaseValueByEnum"))
		return 0;
	}

	return TargetData->GetBaseValue();
}

float UAuraBlueprintFunctionLibrary::GetAttributeCurrentValueByEnum(EAuraAttributeTypes InType, UAuraAttributeSet* InAttributeSet)
{
	if (!IsValid(InAttributeSet))
	{
		UE_LOG(LogTemp, Error, TEXT("UAuraBlueprintFunctionLibrary::GetAttributeBaseValueByEnum, but InAttributeSet==nullptr"));
		return 0;
	}
	auto TargetAttribute = GetGameplayAttributeByEnum(InType);
	if (!TargetAttribute.IsValid())
	{
		return INDEX_NONE;
	}

	FGameplayAttributeData* TargetData = TargetAttribute.GetUProperty()->ContainerPtrToValuePtr<FGameplayAttributeData>(
		InAttributeSet
	);

	if (TargetData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UAuraBlueprintFunctionLibrary::GetAttributeBaseValueByEnum"))
		return 0;
	}

	return TargetData->GetCurrentValue();
}
