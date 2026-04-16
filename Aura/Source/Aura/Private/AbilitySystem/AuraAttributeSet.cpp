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

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealthPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaPoint, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxManaPoint, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthPointAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealthPoint());
	}
	else if (Attribute == GetMaxHealthPointAttribute())
	{
	}
	else if (Attribute == GetManaPointAttribute())
	{
	}
	else if (Attribute == GetMaxManaPointAttribute())
	{
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectPropertiesData EffectPropertiesData;
	SetEffectProperties(Data, EffectPropertiesData);
	if (Data.EvaluatedData.Attribute == GetHealthPointAttribute())
	{
		UE_LOG(LogTemp, Log, TEXT("HP value is %f"), GetHealthPoint());

		UE_LOG(LogTemp, Log, TEXT("HP value from post execute is %f"), Data.EvaluatedData.Magnitude);
	}
}

void UAuraAttributeSet::OnRep_HealthPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthPoint, OldValue);
}

void UAuraAttributeSet::OnRep_MaxHealthPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealthPoint, OldValue);
}

void UAuraAttributeSet::OnRep_ManaPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaPoint, OldValue);
}

void UAuraAttributeSet::OnRep_MaxManaPoint(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxManaPoint, OldValue);
}

void UAuraAttributeSet::SetEffectProperties(
	const FGameplayEffectModCallbackData& InEffectData,
	FEffectPropertiesData&                OutPropsData
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
