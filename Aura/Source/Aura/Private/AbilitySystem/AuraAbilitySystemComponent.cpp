// Copyright NineForce Entertainment

#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGASEnumManager.h"

void UAuraAbilitySystemComponent::AbilityInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
	const FAuraGASEnumManager& Ins = FAuraGASEnumManager::Get();
	// for (auto KeyValuePair : Ins.AttributesTagMapData)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, KeyValuePair.Value.ToString());
	// }
}

void UAuraAbilitySystemComponent::EffectApplied(
	UAbilitySystemComponent*    InTargetASC,
	const FGameplayEffectSpec&  InEffectSpec,
	FActiveGameplayEffectHandle InEffectHandle
)
{
	FGameplayTagContainer TargetTagContainer;
	InEffectSpec.GetAllAssetTags(TargetTagContainer);
	OnEffectAppliedTagContainerDelegate.Broadcast(TargetTagContainer);
}
