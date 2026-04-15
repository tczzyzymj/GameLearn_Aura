// Copyright NineForce Entertainment

#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/Widget//Controller/AuraWidgetController.h"
#include "UI/Widget/Controller/MainPanelWidgetController.h"

void AAuraHUD::InitializeHUD(
	APlayerController*       InPlayerController,
	APlayerState*            InPlayerState,
	UAbilitySystemComponent* InASC,
	UAttributeSet*           InAttributeSet
)
{
	checkf(MainPanelClass, TEXT("AAuraHUD::InitializeHUD, Error! MainPanelClass is empty"));
	checkf(MainPanelWidgetControllerClass, TEXT("AAuraHUD::InitializeHUD, Error! MainPanelClass is empty"));

	FWidgetControllerParams Params(InPlayerController, InPlayerState, InASC, InAttributeSet);
	GetAuraWidgetController(Params);

	MainPanel = CreateWidget<UAuraUserWidget>(GetWorld(), MainPanelClass);
	if (MainPanel)
	{
		MainPanel->AddToViewport();
		MainPanel->SetWidgetController(MainPanelWidgetController);
		MainPanelWidgetController->BroadcastInitialValues();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AuraHUD::BeginPlay(), But Main Panel Class create failed!"));
	}
}

UAuraWidgetController* AAuraHUD::GetAuraWidgetController(const FWidgetControllerParams& InParams)
{
	if (MainPanelWidgetController == nullptr)
	{
		MainPanelWidgetController = NewObject<UMainPanelWidgetController>(this, MainPanelWidgetControllerClass);
		MainPanelWidgetController->SetWidgetControllerParams(InParams);
		MainPanelWidgetController->BindCallbacksToDependencies();
	}

	return MainPanelWidgetController;
}
