// Copyright NineForce Entertainment

#include "Character/AuraEnemy.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Net/UnrealNetwork.h"

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

void AAuraEnemy::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraEnemy, Level);
}

void AAuraEnemy::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityInfoSet();

	InitDefaultAttributes();
}

void AAuraEnemy::OnRep_Level(int32 OldValue)
{
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

int32 AAuraEnemy::GetCharacterLevel()
{
	return Level;
}
