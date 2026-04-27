// Copyright NineForce Entertainment

#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGASEnumManager.h"

void UAuraAbilitySystemComponent::AbilityInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities)
{
	for (const TSubclassOf<UGameplayAbility> SingleAbility : InAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(SingleAbility, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTagFast(AuraAbility->StartupInputTag);

			GiveAbility(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}
}

void UAuraAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	TArray<FGameplayAbilitySpec>& TargetAbilities = GetActivatableAbilities();
	for (FGameplayAbilitySpec& AbilitySpec : TargetAbilities)
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	TArray<FGameplayAbilitySpec>& TargetAbilities = GetActivatableAbilities();
	for (FGameplayAbilitySpec& AbilitySpec : TargetAbilities)
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(
	UAbilitySystemComponent*    InTargetASC,
	const FGameplayEffectSpec&  InEffectSpec,
	FActiveGameplayEffectHandle InEffectHandle
)
{
	FGameplayTagContainer TargetTagContainer;
	InEffectSpec.GetAllAssetTags(TargetTagContainer);
	OnEffectAppliedTagContainerDelegate.Broadcast(TargetTagContainer);
}
