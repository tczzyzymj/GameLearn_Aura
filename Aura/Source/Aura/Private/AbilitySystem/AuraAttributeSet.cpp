// Copyright NineForce Entertainment

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealthPoint(20);
	InitMaxHealthPoint(100);
	InitManaPoint(10);
	InitMaxManaPoint(50);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// vital properties
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthPoint, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaPoint, COND_None, REPNOTIFY_Always);

	// end

	// primary properties
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	//end

	/* Secondary Properties*/
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealthPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxManaPoint, COND_None, REPNOTIFY_Always);

	/* End*/
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthPointAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealthPoint());
	}
	else if (Attribute == GetManaPointAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxManaPoint());
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FAuraEffectPropertiesData EffectPropertiesData;
	SetEffectProperties(Data, EffectPropertiesData);

	if (Data.EvaluatedData.Attribute == GetHealthPointAttribute() ||
	    Data.EvaluatedData.Attribute == GetMaxHealthPointAttribute())
	{
		SetHealthPoint(FMath::Clamp(GetHealthPoint(), 0.0f, GetMaxHealthPoint()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaPointAttribute() ||
	         Data.EvaluatedData.Attribute == GetMaxManaPointAttribute())
	{
		SetManaPoint(FMath::Clamp(GetManaPoint(), 0.0f, GetMaxManaPoint()));
	}
}

/* Vital Properties*/
void UAuraAttributeSet::OnRep_HealthPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthPoint, OldValue);
}

void UAuraAttributeSet::OnRep_ManaPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaPoint, OldValue);
}

/* End Vital Properties */

/* Primary Properties */
void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldValue);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldValue);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldValue);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldValue);
}

/* End Primary Properties */

/* Secondary Properties */
void UAuraAttributeSet::OnRep_MaxHealthPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealthPoint, OldValue);
}

void UAuraAttributeSet::OnRep_MaxManaPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxManaPoint, OldValue);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldValue);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldValue);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldValue);
}

void UAuraAttributeSet::OnRep_CriticalChance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalChance, OldValue);
}

void UAuraAttributeSet::OnRep_CriticalDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalDamage, OldValue);
}

void UAuraAttributeSet::OnRep_CriticalResistance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalResistance, OldValue);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldValue);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldValue);
}

/* end */

void UAuraAttributeSet::SetEffectProperties(
	const FGameplayEffectModCallbackData& InEffectData,
	FAuraEffectPropertiesData&            OutPropsData
)
{
	OutPropsData.EffectContextHandle = InEffectData.EffectSpec.GetContext();

	// Get Source info
	OutPropsData.SourceASC = OutPropsData.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (OutPropsData.SourceASC && OutPropsData.SourceASC->AbilityActorInfo.IsValid() &&
	    OutPropsData.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		auto SourceAbilityActorInfo              = OutPropsData.SourceASC->AbilityActorInfo;
		OutPropsData.SourceAvatarActor           = SourceAbilityActorInfo->AvatarActor.Get();
		OutPropsData.SourceAvatarActorController = SourceAbilityActorInfo->PlayerController.Get();
		if (OutPropsData.SourceAvatarActorController)
		{
			OutPropsData.SourceCharacter = Cast<ACharacter>(OutPropsData.SourceAvatarActorController->GetPawn());
		}
		else if (OutPropsData.SourceAvatarActor)
		{
			OutPropsData.SourceCharacter = Cast<ACharacter>(OutPropsData.SourceAvatarActor);
		}
	}
	// end

	// get Target info
	OutPropsData.TargetASC = &InEffectData.Target;
	if (OutPropsData.TargetASC && OutPropsData.TargetASC->AbilityActorInfo.IsValid() &&
	    OutPropsData.TargetASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		auto AbilityActorInfo                    = OutPropsData.TargetASC->AbilityActorInfo;
		OutPropsData.TargetAvatarActor           = AbilityActorInfo->AvatarActor.Get();
		OutPropsData.TargetAvatarActorController = AbilityActorInfo->PlayerController.Get();
		if (OutPropsData.TargetAvatarActorController)
		{
			OutPropsData.TargetCharacter = Cast<ACharacter>(OutPropsData.TargetAvatarActorController->GetPawn());
		}
		else if (OutPropsData.TargetAvatarActor)
		{
			OutPropsData.TargetCharacter = Cast<ACharacter>(OutPropsData.TargetAvatarActor);
		}
	}

	// end
}
