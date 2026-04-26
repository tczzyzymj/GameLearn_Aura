// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Interaction/EnemyInterface.h"
#include "GameFramework/PlayerController.h"
#include "Input/AuraInputConfigDataAsset.h"
#include "AuraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

	UAuraAbilitySystemComponent* GetASC();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void CursorTrace();

private:
	UPROPERTY(EditAnywhere, Category = "Aura | Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Aura | Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Aura | Input")
	TObjectPtr<UAuraInputConfigDataAsset> InputConfigDataAsset;

	TScriptInterface<IEnemyInterface> LastHoverActor;

	TScriptInterface<IEnemyInterface> CurHoverActor;

	void Move(const FInputActionValue& InputActionValue);

	void AbilityInputPressed(EAuraInputTypes InType);

	void AbilityInputReleased(EAuraInputTypes InType);

	void AbilityInputHeld(EAuraInputTypes InType);

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	FVector CachedDestination = FVector::ZeroVector;

	float LMBPressedTime          = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Aura | PathFind")
	float ShortPressTimeThreshold = 0.15f;
	bool  bAutoRunning            = false;
	bool  bTargeting              = false;

	UPROPERTY(EditDefaultsOnly, Category = "Aura | PathFind")
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
};
