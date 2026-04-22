// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | WidgetController")
	static UAuraWidgetController* GetWidgetController(const UObject* WorldContextObject);
};
