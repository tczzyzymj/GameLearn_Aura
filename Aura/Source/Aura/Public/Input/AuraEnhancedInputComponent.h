// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AuraGASEnumManager.h"
#include "AuraInputConfigDataAsset.h"
#include "EnhancedInputComponent.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressFuncType, typename ReleaseFuncType, typename HoldFuncType>
	void BindAbilityActions(
		const UAuraInputConfigDataAsset* InConfigDataAsset,
		UserClass*                       Object,
		PressFuncType                    PressedFunc,
		ReleaseFuncType                  ReleasedFunc,
		HoldFuncType                     HeldFunc
	);
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(
	const UAuraInputConfigDataAsset* InConfigDataAsset,
	UserClass*                       Object,
	PressedFuncType                  PressedFunc,
	ReleasedFuncType                 ReleasedFunc,
	HeldFuncType                     HeldFunc
)
{
	check(InConfigDataAsset);

	for (const TTuple<EAuraInputTypes, FAuraInputData>& Pair : InConfigDataAsset->AuraInputConfigMapData)
	{
		if (PressedFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Started,
				Object,
				PressedFunc,
				Pair.Key
			);
		}

		if (ReleasedFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Completed,
				Object,
				ReleasedFunc,
				Pair.Key
			);
		}

		if (HeldFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Triggered,
				Object,
				HeldFunc,
				Pair.Key
			);
		}
	}
}
