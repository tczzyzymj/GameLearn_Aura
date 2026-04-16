// Copyright NineForce Entertainment

#include "Actor/AuraGameplayEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayCueNotifyTypes.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AAuraGameplayEffectActor::AAuraGameplayEffectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void AAuraGameplayEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraGameplayEffectActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	InternalTickForStayGameplayEffect(DeltaSeconds);
}

void AAuraGameplayEffectActor::Destroyed()
{
	Super::Destroyed();

	if (ActorInfinityGameplayEffectMap.Num() > 0)
	{
		TArray<TObjectPtr<AActor>> ActorKeys;
		ActorInfinityGameplayEffectMap.GetKeys(ActorKeys);
		for (int i = 0; i < ActorKeys.Num(); ++i)
		{
			OnEndOverlap(ActorKeys[i]);
		}
	}

	ActorStayTimeMap.Empty();
	ActorStayTimeToRemove.Empty();
	ActorInfinityGameplayEffectMap.Empty();
}

void AAuraGameplayEffectActor::InternalTickForStayGameplayEffect(float DeltaSeconds)
{
	if (ActorStayTimeMap.Num() < 1)
	{
		return;
	}

	for (auto KeyValuePair : ActorStayTimeMap)
	{
		for (int i = KeyValuePair.Value.Num(); i >= 0; --i)
		{
			KeyValuePair.Value[i].StayTimeToAdd -= DeltaSeconds;
			if (KeyValuePair.Value[i].StayTimeToAdd <= 0.0f)
			{
				ApplyGameplayEffectToActor(KeyValuePair.Key, KeyValuePair.Value[i]);
				KeyValuePair.Value.RemoveAt(i);
			}
		}

		if (KeyValuePair.Value.Num() < 1)
		{
			ActorStayTimeToRemove.Add(KeyValuePair.Key);
		}
	}

	if (ActorStayTimeToRemove.Num() > 0)
	{
		for (int i = 0; i < ActorStayTimeToRemove.Num(); ++i)
		{
			ActorStayTimeMap.Remove(ActorStayTimeToRemove[i]);
		}
		ActorStayTimeToRemove.Reset();
	}
}

void AAuraGameplayEffectActor::ApplyGameplayEffectToActor(AActor* InTargetActor, const FAuraGameplayEffectData& InAuraGameplayEffectData)
{
	if (InTargetActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAuraGameplayEffectActor::ApplyEffectToActor, Target actor is empty!"));
		return;
	}

	if (InAuraGameplayEffectData.GameplayEffectClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAuraGameplayEffectActor::ApplyEffectToActor, InEffectClass is empty!"));
		return;
	}

	const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);
	if (TargetASC == nullptr)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("AAuraGameplayEffectActor::ApplyEffectToActor, Target actor : %s, don't have AbilitySystemComponent"),
			*InTargetActor->GetName()
		);
		return;
	}

	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle TargetEffectSpecHandle = TargetASC->MakeOutgoingSpec(
		InAuraGameplayEffectData.GameplayEffectClass,
		Level,
		ContextHandle
	);
	FActiveGameplayEffectHandle TargetGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*TargetEffectSpecHandle.Data.Get());

	if (TargetGameplayEffectHandle.IsValid())
	{
		if (InAuraGameplayEffectData.RemovePolicy == EGameplayEffectRemovePolicy::OnEndOverlap &&
		    TargetEffectSpecHandle.Data->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
		{
			if (ActorInfinityGameplayEffectMap.Contains(InTargetActor))
			{
				ActorInfinityGameplayEffectMap[InTargetActor].Add(TargetGameplayEffectHandle);
			}
			else
			{
				TArray<FActiveGameplayEffectHandle> HandleArray;
				HandleArray.Add(TargetGameplayEffectHandle);
				ActorInfinityGameplayEffectMap.Add(InTargetActor, HandleArray);
			}
		}
	}
}

void AAuraGameplayEffectActor::OnBeginOverlap(AActor* InTargetActor)
{
	if (InTargetActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAuraGameplayEffectActor::OnBeginOverlap, Target actor is empty!"));
		return;
	}

	for (int i = 0; i < GameplayEffectDataArray.Num(); ++i)
	{
		switch (GameplayEffectDataArray[i].AddPolicy)
		{
			case EGameplayEffectAddPolicy::OnBeginOverlap:
			{
				ApplyGameplayEffectToActor(InTargetActor, GameplayEffectDataArray[i]);
				break;
			}
			case EGameplayEffectAddPolicy::OnEndOverlap:
			{
				break;
			}
			case EGameplayEffectAddPolicy::OnStayForSpecificTime:
			{
				if (!ActorStayTimeMap.Contains(InTargetActor))
				{
					TArray<FAuraGameplayEffectData> StayTimeDataArray;
					StayTimeDataArray.Add(GameplayEffectDataArray[i]);
					ActorStayTimeMap.Add(InTargetActor, StayTimeDataArray);
				}
				else
				{
					ActorStayTimeMap[InTargetActor].Add(GameplayEffectDataArray[i]);
				}

				break;
			}
			default:
			{
				UE_LOG(
					LogTemp,
					Error,
					TEXT("AddPolicy : %s Not Implemented"),
					*StaticEnum<EGameplayEffectAddPolicy>()->GetNameStringByIndex((uint8)GameplayEffectDataArray[i].AddPolicy)
				);
				break;
			}
		}
	}
}

void AAuraGameplayEffectActor::OnEndOverlap(AActor* InTargetActor)
{
	if (InTargetActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAuraGameplayEffectActor::OnEndOverlap, Target actor is empty!"));
		return;
	}

	ActorStayTimeMap.Remove(InTargetActor);

	if (ActorInfinityGameplayEffectMap.Contains(InTargetActor))
	{
		const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);
		if (TargetASC != nullptr)
		{
			auto DataArray = ActorInfinityGameplayEffectMap[InTargetActor];
			for (int i = 0; i < DataArray.Num(); ++i)
			{
				TargetASC->RemoveActiveGameplayEffect(DataArray[i], 1);
			}
		}
	}

	ActorInfinityGameplayEffectMap.Remove(InTargetActor);
}
