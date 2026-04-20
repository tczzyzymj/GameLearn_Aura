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

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;
	
	virtual int32 GetCharacterLevel() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Aura Combat")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, Category = "Aura Combat")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing=OnRep_Level, Category = "Aura Combat")
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldValue);
};
