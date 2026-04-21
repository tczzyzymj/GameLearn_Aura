// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AuraGameDefine.h"
#include "GameplayTagContainer.h"

/**
 * Singleton containing native GameplayTags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get()
	{
		return Ins;
	}

	static void InitNativeGameplayTags();
	
	static FGameplayTag GetGameplayTagByAttributeType(EAuraAttributeTypes InAttributeType);

	TMap<EAuraAttributeTypes,FGameplayTag> AttributesTagMapData;
protected:
private:
	static FAuraGameplayTags Ins;
};
