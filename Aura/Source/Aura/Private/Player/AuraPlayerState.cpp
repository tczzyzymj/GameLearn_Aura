// Copyright NineForce Entertainment

#include "Player/AuraPlayerState.h"

#include "AuraGameDefine.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Net/UnrealNetwork.h"

using FGetterFunc = float (UAuraAttributeSet::*)() const;

AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(NET_UPDATE_FREQUENCY);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	// TMap<EAuraAttributeTypes, FGetterFunc> MapData;
	// MapData.Add(EAuraAttributeTypes::HealthPoint, &UAuraAttributeSet::GetHealthPoint);
	// auto TargetAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	// if (auto Func = MapData.Find(EAuraAttributeTypes::HealthPoint))
	// {
	// 	float Health = (TargetAttributeSet->*(*Func))();
	// 	UE_LOG(LogTemp, Warning, TEXT("Health is %f"), Health);
	// }
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraPlayerState, Level);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

int32 AAuraPlayerState::GetCharacterLevel()
{
	return Level;
}

void AAuraPlayerState::OnRep_Level(int32 OldValue)
{
}
