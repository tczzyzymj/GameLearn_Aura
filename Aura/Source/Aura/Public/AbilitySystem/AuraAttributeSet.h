// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
	UAuraAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthPoint, Category = "Vital Attribute")
	FGameplayAttributeData HealthPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, HealthPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealthPoint, Category = "Vital Attribute")
	FGameplayAttributeData MaxHealthPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxHealthPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaPoint, Category = "Vital Attribute")
	FGameplayAttributeData ManaPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ManaPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxManaPoint, Category = "Vital Attribute")
	FGameplayAttributeData MaxManaPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxManaPoint);

	UFUNCTION()
	void OnRep_HealthPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealthPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ManaPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxManaPoint(const FGameplayAttributeData& OldValue);
};
