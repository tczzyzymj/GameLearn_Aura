// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

USTRUCT()
struct FAuraEffectPropertiesData
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor;

	UPROPERTY()
	TObjectPtr<AController> SourceAvatarActorController;

	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC;

	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor;

	UPROPERTY()
	TObjectPtr<AController> TargetAvatarActorController;

	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
	UAuraAttributeSet();

	/* Vital Properties */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthPoint, Category = "Vital Attribute")
	FGameplayAttributeData HealthPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, HealthPoint);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaPoint, Category = "Vital Attribute")
	FGameplayAttributeData ManaPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ManaPoint);

	UFUNCTION()
	void OnRep_HealthPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ManaPoint(const FGameplayAttributeData& OldValue);

	/* End Vital Properties */

	/* Primary Properties */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Strength, Category = "Vital Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Intelligence, Category = "Vital Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resilience, Category = "Vital Attribute")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Vigor, Category = "Vital Attribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldValue);

	/* end Primary Properties */

	/* secondary properties */

	// max hp , based on Vigor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealthPoint, Category = "Secondary Attribute")
	FGameplayAttributeData MaxHealthPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxHealthPoint);

	// max mana point, based on Intelligence 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxManaPoint, Category = "Secondary Attribute")
	FGameplayAttributeData MaxManaPoint;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, MaxManaPoint);

	// reduce physical damage, based on Resilience
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Armor, Category = "Secondary Attribute")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, Armor);

	// ignores percentage of enemy's armor, based on Resilience
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ArmorPenetration, Category = "Secondary Attribute")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ArmorPenetration);

	// reduce incoming damage to half, based on Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BlockChance, Category = "Secondary Attribute")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, BlockChance);

	// make damage multiply CriticalDamagePercent , based on ArmorPenetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalChance, Category = "Secondary Attribute")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalChance);

	// extra value added when critical happened, based on ArmorPenetration
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalDamagePercent, Category = "Secondary Attribute")
	FGameplayAttributeData CriticalDamagePercent;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalDamagePercent);

	// reduce critical chance, based on Armor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalResistance, Category = "Secondary Attribute")
	FGameplayAttributeData CriticalResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CriticalDamagePercentResistance, Category = "Secondary Attribute")
	FGameplayAttributeData CriticalDamagePercentResistance;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, CriticalDamagePercentResistance);

	// how much health point auto add, per 1 second, based on Vigor
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegeneration, Category = "Secondary Attribute")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, HealthRegeneration);

	// how much mana point auto add per 1 second, based on Intelligence
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegeneration, Category = "Secondary Attribute")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS_BASIC(UAuraAttributeSet, ManaRegeneration);

	UFUNCTION()
	void OnRep_MaxManaPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealthPoint(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalDamagePercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_CriticalResistance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	void OnRep_CriticalDamagePercentResistance(const FGameplayAttributeData& OldValue);

	/* end secondary properties*/

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

protected:
	void SetEffectProperties(const FGameplayEffectModCallbackData& InEffectData, FAuraEffectPropertiesData& OutPropsData);
};
