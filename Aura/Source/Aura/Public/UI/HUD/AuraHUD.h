// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget/Controller/AuraWidgetController.h"
#include "UI/Widget/Controller/AttributeMenuWidgetController.h"
#include "UI/Widget/Controller/MainPanelWidgetController.h"
#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
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

	UAuraWidgetController* GetMainPanelWidgetController(const FWidgetControllerParams& InParams);

	UAuraWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& InParams);

protected:

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> MainPanelClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainPanelWidgetController> MainPanelWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UMainPanelWidgetController> MainPanelWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
};
