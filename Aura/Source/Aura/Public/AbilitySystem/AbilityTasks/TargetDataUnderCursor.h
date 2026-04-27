// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCursor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCursorTargetDataSignature, const FVector&, InData);

/**
 * 
 */
UCLASS()
class AURA_API UTargetDataUnderCursor : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(
		BlueprintCallable,
		Category="Aura | GAS | AbilityTask",
		meta=(HidePin="InOwingAbility", DefaultToSelf="InOwingAbility", BlueprintInternalUseOnly="true")
	)
	static UTargetDataUnderCursor* CreateTargetDataUnderCursor(UGameplayAbility* InOwingAbility);
	
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FCursorTargetDataSignature ValidData;
};
