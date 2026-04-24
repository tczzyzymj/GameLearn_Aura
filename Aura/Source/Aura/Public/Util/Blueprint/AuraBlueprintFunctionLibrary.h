// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraGameDefine.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UI/Widget/Controller/AuraWidgetController.h"
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
	static UAuraWidgetController* GetMainPanelWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Enum")
	static UAuraWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Enum")
	static EAuraAttributeTypes GetEAttributeTypeByIndex(int32 InIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Enum")
	static FGameplayTag GetGameplayTagByEnum(EAuraAttributeTypes InType);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Enum")
	static FGameplayAttribute GetGameplayAttributeByEnum(EAuraAttributeTypes InType);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Attribute")
	static float GetAttributeBaseValueByEnum(EAuraAttributeTypes InType, UAuraAttributeSet* InAttributeSet);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Aura | AbilitySystemLibrary | Attribute")
	static float GetAttributeCurrentValueByEnum(EAuraAttributeTypes InType, UAuraAttributeSet* InAttributeSet);
};
