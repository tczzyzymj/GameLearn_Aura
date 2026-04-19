// Copyright NineForce Entertainment

#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraAbilitySystemComponent::AbilityInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
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
