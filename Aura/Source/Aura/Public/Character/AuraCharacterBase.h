// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Interaction/AuraCombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public IAuraCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> InGameplayEffect, float InLevel) const;

	virtual void InitAbilityActorInfo();

	void InitDefaultAttributes() const;
	
	void AddCharacterAbilities();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aura | GAS Init")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesGameplayEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aura | GAS Init")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesGameplayEffect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Aura | GAS Init")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesGameplayEffect;
private:
	UPROPERTY(EditAnywhere, Category = "Aura | GAS Init")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
