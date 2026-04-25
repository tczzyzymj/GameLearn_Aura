// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Ability/AuraGameplayAbility.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAppliedTagContainerDelegate, const FGameplayTagContainer&)

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);

	FOnEffectAppliedTagContainerDelegate OnEffectAppliedTagContainerDelegate;

protected:
	void EffectApplied(
		UAbilitySystemComponent*    InTargetASC,
		const FGameplayEffectSpec&  InEffectSpec,
		FActiveGameplayEffectHandle InEffectHandle
	);
};
