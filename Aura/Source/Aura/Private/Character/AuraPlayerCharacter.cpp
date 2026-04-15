// Copyright NineForce Entertainment

#include "Character/AuraPlayerCharacter.h"

#include "AbilitySystemComponent.h"
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

void AAuraPlayerCharacter::InternalInitAbilityActorInfo()
{
	auto TargetPlayerState = GetPlayerState<AAuraPlayerState>();
	auto TargetComponent   = TargetPlayerState->GetAbilitySystemComponent();
	TargetComponent->InitAbilityActorInfo(TargetPlayerState, this);

	AbilitySystemComponent = TargetComponent;
	AttributeSet           = TargetPlayerState->GetAttributeSet();

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

	InternalInitAbilityActorInfo();
}

void AAuraPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InternalInitAbilityActorInfo();
}
