// Copyright NineForce Entertainment

#include "UI/Widget/Controller/MainPanelWidgetController.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetHealthPointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Attribute)
		{
			OnHealthPointChanged.Broadcast(Attribute.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetMaxHealthPointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Attribute)
		{
			OnMaxHealthPointChanged.Broadcast(Attribute.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetManaPointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Attribute)
		{
			OnManaPointChanged.Broadcast(Attribute.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttribute->GetMaxManaPointAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Attribute)
		{
			if (Attribute.GEModData)
			{
				// Attribute.GEModData->EffectSpec.GetAllAssetTags()
			}
			OnMaxManaPointChanged.Broadcast(Attribute.NewValue);
		}
	);
	if (auto TargetAuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		TargetAuraASC->OnEffectAppliedTagContainerDelegate.AddLambda(
			[this](const FGameplayTagContainer& InContainer)
			{
				if (MessageWidgetDataTable == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("MessageWidgetDataTable is nullptr"));
					return;
				}
				auto TargetTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				for (const auto& Tag : InContainer)
				{
					if (Tag.MatchesTag(TargetTag))
					{
						if (auto TargetRowData = MessageWidgetDataTable->FindRow<FUIWidgetDataRow>(Tag.GetTagName(), TEXT("")))
						{
							OnMessageWidget.Broadcast(*TargetRowData);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("MessageWidgetDataTable doesn't contains key : %s"), *Tag.ToString());
						}
					}
				}
			}
		);
	}
}
