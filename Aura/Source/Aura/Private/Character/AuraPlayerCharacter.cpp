// Copyright NineForce Entertainment

#include "Character/AuraPlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
