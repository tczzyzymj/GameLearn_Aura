// Copyright NineForce Entertainment

#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitDefaultAttributes() const
{
	ApplyGameplayEffectToSelf(DefaultPrimaryAttributesGameplayEffect, 1);
	ApplyGameplayEffectToSelf(DefaultSecondaryAttributesGameplayEffect, 1);
	ApplyGameplayEffectToSelf(DefaultVitalAttributesGameplayEffect, 1);
}

void AAuraCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority())
	{
		return;
	}

	if (auto TargetASC = CastChecked<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		TargetASC->AddCharacterAbilities(StartupAbilities);
	}
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacterBase::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> InGameplayEffect, float InLevel) const
{
	if (InGameplayEffect == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AAuraCharacterBase::ApplyGameplayEffectToSelf, InGameplayEffect is nullptr!"));
		return;
	}
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent();
	check(TargetASC);
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec = TargetASC->MakeOutgoingSpec(
		InGameplayEffect,
		InLevel,
		EffectContext
	);
	FActiveGameplayEffectHandle EffectHandle = TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), TargetASC);
	if (!EffectHandle.WasSuccessfullyApplied())
	{
		UE_LOG(LogTemp, Error, TEXT("Initialize apply GameplayEffect failed! Please check!"));
	}
}
