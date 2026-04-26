// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/AuraGameplayAbility.h"
#include "Actor/AuraProjectileActor.h"
#include "AuraProjectileSpellAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpellAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle     Handle,
		const FGameplayAbilityActorInfo*     ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData*            TriggerEventData
	) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectileActor> ProjectileActorClass;
};
