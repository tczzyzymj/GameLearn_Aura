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
		PressFuncType                    PressFunc,
		ReleaseFuncType                  ReleaseFunc,
		HoldFuncType                     HoldFunc
	);
};

template<class UserClass, typename PressFuncType, typename ReleaseFuncType, typename HoldFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(
	const UAuraInputConfigDataAsset* InConfigDataAsset,
	UserClass*                       Object,
	PressFuncType                    PressFunc,
	ReleaseFuncType                  ReleaseFunc,
	HoldFuncType                     HoldFunc
)
{
	check(InConfigDataAsset);

	for (const TTuple<EAuraInputTypes, FAuraInputData>& Pair : InConfigDataAsset->AuraInputConfigMapData)
	{
		if (PressFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Started,
				Object,
				PressFunc,
				Pair.Key
			);
		}

		if (ReleaseFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Completed,
				Object,
				ReleaseFunc,
				Pair.Key
			);
		}

		if (HoldFunc)
		{
			BindAction(
				Pair.Value.InputAction,
				ETriggerEvent::Triggered,
				Object,
				HoldFunc,
				Pair.Key
			);
		}
	}
}
