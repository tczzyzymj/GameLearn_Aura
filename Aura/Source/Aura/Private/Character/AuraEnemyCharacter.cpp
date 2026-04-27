// Copyright NineForce Entertainment

#include "Character/AuraEnemyCharacter.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"
#include "Net/UnrealNetwork.h"

AAuraEnemyCharacter::AAuraEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

void AAuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AAuraEnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAuraEnemyCharacter, Level);
}

void AAuraEnemyCharacter::InitAbilityActorInfo()
{
	check(AbilitySystemComponent);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityInfoSet();

	InitDefaultAttributes();
}

void AAuraEnemyCharacter::OnRep_Level(int32 OldValue)
{
}

void AAuraEnemyCharacter::HighlightActor()
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

void AAuraEnemyCharacter::UnHighlightActor()
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

int32 AAuraEnemyCharacter::GetCharacterLevel()
{
	return Level;
}
