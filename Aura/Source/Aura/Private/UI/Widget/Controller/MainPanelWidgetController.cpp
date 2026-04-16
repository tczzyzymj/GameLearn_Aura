// Copyright NineForce Entertainment

#include "UI/Widget/Controller/MainPanelWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UMainPanelWidgetController::BroadcastInitialValues()
{
	auto TargetAttribute = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthPointChanged.Broadcast(TargetAttribute->GetHealthPoint());
	OnMaxHealthPointChanged.Broadcast(TargetAttribute->GetMaxHealthPoint());
	OnManaPointChanged.Broadcast(TargetAttribute->GetManaPoint());
	OnMaxManaPointChanged.Broadcast(TargetAttribute->GetMaxManaPoint());
}

void UMainPanelWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	auto TargetAttribute = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetHealthPointAttribute()).AddUObject(
		this,
		&UMainPanelWidgetController::HealthPointChanged
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetMaxHealthPointAttribute()).AddUObject(
		this,
		&UMainPanelWidgetController::MaxHealthPointChanged
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetManaPointAttribute()).AddUObject(
		this,
		&UMainPanelWidgetController::ManaPointChanged
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetMaxManaPointAttribute()).AddUObject(
		this,
		&UMainPanelWidgetController::MaxManaPointChanged
	);
}

void UMainPanelWidgetController::HealthPointChanged(const FOnAttributeChangeData& InData) const
{
	OnHealthPointChanged.Broadcast(InData.NewValue);
}

void UMainPanelWidgetController::MaxHealthPointChanged(const FOnAttributeChangeData& InData) const
{
	OnMaxHealthPointChanged.Broadcast(InData.NewValue);
}

void UMainPanelWidgetController::ManaPointChanged(const FOnAttributeChangeData& InData) const
{
	OnManaPointChanged.Broadcast(InData.NewValue);
}

void UMainPanelWidgetController::MaxManaPointChanged(const FOnAttributeChangeData& InData) const
{
	OnMaxManaPointChanged.Broadcast(InData.NewValue);
}
