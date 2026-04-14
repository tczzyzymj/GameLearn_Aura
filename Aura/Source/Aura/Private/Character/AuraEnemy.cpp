// Copyright NineForce Entertainment

#include "Character/AuraEnemy.h"
#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
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
