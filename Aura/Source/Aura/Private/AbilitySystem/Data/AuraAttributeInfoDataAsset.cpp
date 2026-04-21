// Copyright NineForce Entertainment

#include "AbilitySystem/Data/AuraAttributeInfoDataAsset.h"

FAuraAttributeInfoData UAuraAttributeInfoDataAsset::FindAttributeInfoDataByTag(const FGameplayTag& InTag, bool bLogNotFound)
{
	for (const FAuraAttributeInfoData& InfoData : AuraAttributeInfos)
	{
		if (InfoData.AttributeTag.MatchesTagExact(InTag))
		{
			return InfoData;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Can't find GameplayTag :[%s] InfoData on AttributeInfo : [%s]"),
			*InTag.ToString(),
			*GetNameSafe(this)
		);
	}
	return FAuraAttributeInfoData();
}
