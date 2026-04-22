// Copyright NineForce Entertainment

#include "Util/Blueprint/AuraBlueprintFunctionLibrary.h"

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
		return AuraHUD->GetAuraWidgetController(Params);
	}

	return nullptr;
}
