// Copyright NineForce Entertainment

#include "Character/AuraPlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Aura/Public/Player/AuraPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"

AAuraPlayerCharacter::AAuraPlayerCharacter()
{
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate              = FRotator(0.0f, 400.0f, 0.0f);
		MovementComponent->bConstrainToPlane         = true;
		MovementComponent->bSnapToPlaneAtStart       = true;

		bUseControllerRotationPitch = false;
		bUseControllerRotationRoll  = false;
		bUseControllerRotationYaw   = false;
	}
}

void AAuraPlayerCharacter::InitAbilityActorInfo()
{
	auto TargetPlayerState = GetPlayerState<AAuraPlayerState>();
	check(TargetPlayerState);
	AbilitySystemComponent = TargetPlayerState->GetAbilitySystemComponent();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(TargetPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityInfoSet();
	AttributeSet = TargetPlayerState->GetAttributeSet();

	if (auto PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (auto TargetHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			TargetHUD->InitializeHUD(PlayerController, TargetPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

// this is executed by server
void AAuraPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void AAuraPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}
