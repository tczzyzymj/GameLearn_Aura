// Copyright NineForce Entertainment


#include "AbilitySystem/AbilityTasks/TargetDataUnderCursor.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::CreateTargetDataUnderCursor(UGameplayAbility* InOwingAbility)
{
	UTargetDataUnderCursor* TargetDataUnderCursor = NewAbilityTask<UTargetDataUnderCursor>(InOwingAbility);

	return TargetDataUnderCursor;
}

void UTargetDataUnderCursor::Activate()
{
	if (GetOwnerActor()->HasAuthority())
	{
		TWeakObjectPtr<APlayerController> PC = Ability->GetCurrentActorInfo()->PlayerController;
		if (PC.IsValid())
		{
			FHitResult HitResult;
			if (PC->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
			{
				ValidData.Broadcast(HitResult.GetActor()->GetActorLocation());
			}
		}
	}
}
