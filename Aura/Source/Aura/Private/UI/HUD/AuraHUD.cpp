// Copyright NineForce Entertainment

#include "UI/HUD/AuraHUD.h"

void AAuraHUD::InitializeHUD(
	APlayerController*       InPlayerController,
	APlayerState*            InPlayerState,
	UAbilitySystemComponent* InASC,
	UAttributeSet*           InAttributeSet
)
{
	checkf(MainPanelClass, TEXT("AAuraHUD::InitializeHUD, Error! MainPanelClass is empty"));

	FWidgetControllerParams Params(InPlayerController, InPlayerState, InASC, InAttributeSet);
	GetMainPanelWidgetController(Params);

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

UAuraWidgetController* AAuraHUD::GetMainPanelWidgetController(const FWidgetControllerParams& InParams)
{
	if (MainPanelWidgetController == nullptr)
	{
		MainPanelWidgetController = NewObject<UMainPanelWidgetController>(this, UMainPanelWidgetController::StaticClass());
		MainPanelWidgetController->SetWidgetControllerParams(InParams);
		MainPanelWidgetController->BindCallbacksToDependencies();
	}

	return MainPanelWidgetController;
}

UAuraWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& InParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(
			this,
			UAttributeMenuWidgetController::StaticClass()
		);
		AttributeMenuWidgetController->SetWidgetControllerParams(InParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return MainPanelWidgetController;
}
