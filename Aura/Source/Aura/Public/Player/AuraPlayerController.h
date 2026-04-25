// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
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
	
	void AbilityInputPress(EAuraInputTypes InType);
	
	void AbilityInputRelease(EAuraInputTypes InType);
	
	void AbilityInputHold(EAuraInputTypes InType);

	// UFUNCTION()
	// void LeftMouseBtn(const FInputActionValue& InputActionValue);
	//
	// UFUNCTION()
	// void RightMouseBtn(const FInputActionValue& InputActionValue);
	//
	// UFUNCTION()
	// void Keyboard_1(const FInputActionValue& InputActionValue);
	//
	// UFUNCTION()
	// void Keyboard_2(const FInputActionValue& InputActionValue);
	//
	// UFUNCTION()
	// void Keyboard_3(const FInputActionValue& InputActionValue);
	//
	// UFUNCTION()
	// void Keyboard_4(const FInputActionValue& InputActionValue);
};
