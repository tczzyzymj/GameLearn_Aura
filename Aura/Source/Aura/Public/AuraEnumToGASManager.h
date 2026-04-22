// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraGameDefine.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native GameplayTags
 */

struct FAuraEnumToGASManager
{
public:
	static FAuraEnumToGASManager& Get()
	{
		static FAuraEnumToGASManager Ins;
		return Ins;
	}
	
	static void Init();

	static FGameplayTag GetGameplayTagByAttributeType(EAuraAttributeTypes InAttributeType);

protected:
	TMap<EAuraAttributeTypes, FGameplayTag> EnumToTagMapData;

	TMap<EAuraAttributeTypes, FGameplayAttribute> EnumToAttributeMapData;
};
