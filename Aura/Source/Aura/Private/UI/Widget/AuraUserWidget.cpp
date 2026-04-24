// Copyright NineForce Entertainment

#include "UI/Widget/AuraUserWidget.h"

#include "UI/Widget/Controller/AuraWidgetController.h"

void UAuraUserWidget::SetWidgetController(UAuraWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}

void UAuraUserWidget::FinishDestroy()
{
	Super::FinishDestroy();

	if (WidgetController)
	{
		WidgetController.Get()->RemoveBindDelegate(this);
	}
}
