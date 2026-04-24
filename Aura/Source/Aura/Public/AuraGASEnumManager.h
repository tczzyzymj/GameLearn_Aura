// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraGameDefine.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native GameplayTags
 */

struct FAuraGASEnumManager
{
public:
	static FAuraGASEnumManager& Get()
	{
		static FAuraGASEnumManager Ins;
		return Ins;
	}

	static void Init();

	static FGameplayTag GetGameplayTagByEnum(EAuraAttributeTypes InAttributeType);

	static FGameplayAttribute GetGameplayAttributeByEnum(EAuraAttributeTypes InAttributeType);
	
	static EAuraAttributeTypes GetAttributeEnum(const FGameplayAttribute& InAttributeType);

protected:
	TMap<EAuraAttributeTypes, FGameplayTag> EnumToTagMapData;

	TMap<EAuraAttributeTypes, FGameplayAttribute> EnumToAttributeMapData;
	
	TMap<FGameplayAttribute, EAuraAttributeTypes> AttributeToEnumMapData;
};
