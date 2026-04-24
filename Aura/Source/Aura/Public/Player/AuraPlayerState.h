// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Interaction/AuraCombatInterface.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface, public IAuraCombatInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Aura | GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Aura | GAS")
	UAttributeSet* GetAttributeSet() const;

	UFUNCTION(BlueprintCallable, Category = "Aura | GAS")
	virtual int32 GetCharacterLevel() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Aura | GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Aura | GAS")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing=OnRep_Level, Category = "Aura | PlayerCharacter")
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldValue);
};
