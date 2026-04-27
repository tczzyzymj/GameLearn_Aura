// Copyright NineForce Entertainment

#include "AbilitySystem/Ability/AuraProjectileSpellAbility.h"

#include "Interaction/AuraCombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraProjectileSpellAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle     Handle,
	const FGameplayAbilityActorInfo*     ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData*            TriggerEventData
)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpellAbility::CreateProjectile() const
{
	if (GetAvatarActorFromActorInfo()->HasAuthority())
	{
		if (ProjectileActorClass)
		{
			FTransform SpawnTransform;
			FVector    ActorForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
			SpawnTransform.SetRotation(ActorForward.ToOrientationQuat());
			AActor*    OwningActor  = GetOwningActorFromActorInfo();
			check(OwningActor);
			if (IAuraCombatInterface* CombatInterface = Cast<IAuraCombatInterface>(GetAvatarActorFromActorInfo()))
			{
				SpawnTransform.SetLocation(CombatInterface->GetWeaponSocketLocation());
			}
			else
			{
				SpawnTransform.SetLocation(OwningActor->GetActorLocation());
			}
			AAuraProjectileActor* SpawnActor = GetWorld()->SpawnActorDeferred<AAuraProjectileActor>(
				ProjectileActorClass,
				SpawnTransform,
				OwningActor,
				Cast<APawn>(OwningActor),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);
			SpawnActor->FinishSpawning(SpawnTransform);
		}
	}
}
