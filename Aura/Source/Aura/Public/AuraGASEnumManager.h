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

	static const FGameplayTag& GetAttributeGameplayTagByEnum(EAuraAttributeTypes InAttributeType);
	
	static const FGameplayTag& GetInputGameplayTagByEnum(EAuraInputTypes InType);

	static FGameplayAttribute GetGameplayAttributeByEnum(EAuraAttributeTypes InAttributeType);

	static EAuraAttributeTypes GetAttributeEnum(const FGameplayAttribute& InAttributeType);
protected:
	void InternalInitForAttributes();

	void InternalInitForInputTags();

	TMap<EAuraAttributeTypes, FGameplayTag> AttributeEnumToTagMapData;

	TMap<EAuraAttributeTypes, FGameplayAttribute> AttributeEnumToGAMapData;

	TMap<FGameplayAttribute, EAuraAttributeTypes> AttributeToAttriEnumMapData;
	
	TMap<EAuraInputTypes, FGameplayTag> InputEnumToTagMapData;
	
	FGameplayTag InvalidGameplayTag;
};
