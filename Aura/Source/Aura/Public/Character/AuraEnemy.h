// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/AuraCombatInterface.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

	AAuraEnemy();

public:
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

	virtual int32 GetCharacterLevel() override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	bool bHighlighted;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(VisibleAnywhere, Replicated, ReplicatedUsing=OnRep_Level, Category = "Aura Combat")
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldValue);
};
