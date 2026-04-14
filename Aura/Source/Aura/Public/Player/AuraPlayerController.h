// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "GameFramework/PlayerController.h"
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
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	TScriptInterface<IEnemyInterface> LastHoverActor;
	TScriptInterface<IEnemyInterface> CurHoverActor;

	void Move(const FInputActionValue& InputActionValue);
};
