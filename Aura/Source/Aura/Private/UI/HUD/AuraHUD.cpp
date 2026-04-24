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
	check(MainPanelWidgetControllerClass);
	MainPanelWidgetController = NewObject<UMainPanelWidgetController>(this, MainPanelWidgetControllerClass);
	MainPanelWidgetController->SetWidgetControllerParams(InParams);
	MainPanelWidgetController->BindCallbacksToDependencies();

	return MainPanelWidgetController;
}

UAuraWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& InParams)
{
	check(AttributeMenuWidgetControllerClass);

	AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(
		this,
		AttributeMenuWidgetControllerClass
	);
	AttributeMenuWidgetController->SetWidgetControllerParams(InParams);
	AttributeMenuWidgetController->BindCallbacksToDependencies();

	return AttributeMenuWidgetController;
}
