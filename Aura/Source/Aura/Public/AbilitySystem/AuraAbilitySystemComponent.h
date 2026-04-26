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
	FOnEffectAppliedTagContainerDelegate OnEffectAppliedTagContainerDelegate;

	void AbilityInfoSet();

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InAbilities);

	void AbilityInputPressed(const FGameplayTag& InputTag);

	void AbilityInputReleased(const FGameplayTag& InputTag);

	void AbilityInputHeld(const FGameplayTag& InputTag);

protected:
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(
		UAbilitySystemComponent*    InTargetASC,
		const FGameplayEffectSpec&  InEffectSpec,
		FActiveGameplayEffectHandle InEffectHandle
	);
};
