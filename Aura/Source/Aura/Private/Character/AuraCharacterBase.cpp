// Copyright NineForce Entertainment

#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"

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

void AAuraCharacterBase::InitializeDefaultPrimaryAttributes()
{
	UAbilitySystemComponent* TargetASC = GetAbilitySystemComponent();
	check(TargetASC);
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpec = TargetASC->MakeOutgoingSpec(
		DefaultPrimaryAttributesGameplayEffect,
		1,
		EffectContext
	);
	FActiveGameplayEffectHandle EffectHandle = TargetASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), TargetASC);
	if (!EffectHandle.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Initialize apply GameplayEffect failed! Please check!"));
	}
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
