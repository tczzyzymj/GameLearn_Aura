// Copyright NineForce Entertainment

#include "Actor/AuraGameplayEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
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

void AAuraGameplayEffectActor::ApplyEffectToActor(AActor* InTargetActor, TSubclassOf<UGameplayEffect> InEffectClass)
{
	auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor);
	if (TargetASC == nullptr)
	{
		return;
	}

	if (InEffectClass == nullptr)
	{
		return;
	}

	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle TargetEffectSpecHandle = TargetASC->MakeOutgoingSpec(InEffectClass, 1, ContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*TargetEffectSpecHandle.Data.Get());
}
