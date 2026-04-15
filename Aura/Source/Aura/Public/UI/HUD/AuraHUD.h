// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
class UMainPanelWidgetController;
class UAuraWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
class UAuraUserWidget;

/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> MainPanel;

	void InitializeHUD(
		APlayerController*       InPlayerController,
		APlayerState*            InPlayerState,
		UAbilitySystemComponent* ASC,
		UAttributeSet*           InAttributeSet
	);

	UAuraWidgetController* GetAuraWidgetController(const FWidgetControllerParams& InParams);

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> MainPanelClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainPanelWidgetController> MainPanelWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UMainPanelWidgetController> MainPanelWidgetController;
};
