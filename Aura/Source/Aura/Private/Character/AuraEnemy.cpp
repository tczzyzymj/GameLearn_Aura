// Copyright NineForce Entertainment

#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AAuraEnemy::InitAbilityActorInfo()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityInfoSet();
	}
}

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
	if (USkeletalMeshComponent* TargetMesh = GetMesh())
	{
		TargetMesh->SetRenderCustomDepth(true);
		TargetMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

	if (Weapon && Weapon.Get() != nullptr)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;

	if (USkeletalMeshComponent* TargetMesh = GetMesh())
	{
		TargetMesh->SetRenderCustomDepth(false);
	}

	if (Weapon && Weapon.Get() != nullptr)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}
