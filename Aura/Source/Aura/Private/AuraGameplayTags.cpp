// Copyright NineForce Entertainment

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::Ins;

void FAuraGameplayTags::InitNativeGameplayTags()
{
	auto TargetEnum = StaticEnum<EAuraAttributeTypes>();
	for (int Index = 0; Index < TargetEnum->NumEnums() - 1; ++Index)
	{
		auto Importance = TargetEnum->GetMetaData(TEXT("Importance"), Index);
		checkf(
			!Importance.IsEmpty(),
			TEXT("Enum : %s no Importance MetaData, Please check"),
			*TargetEnum->GetAuthoredNameStringByIndex(Index)
		);

		auto TagDevComment = TargetEnum->GetMetaData(TEXT("TagDevComment"), Index);

		FString TagName = FString::Printf(
			TEXT("Attributes.%s.%s"),
			*Importance,
			*TargetEnum->GetAuthoredNameStringByIndex(Index)
		);

		FName        FinalName(TagName);
		FGameplayTag TargetTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FinalName,
			TagDevComment
		);
		if (TargetTag.IsValid())
		{
			Ins.AttributesTagMapData.Add(static_cast<EAuraAttributeTypes>(Index), TargetTag);
		}
	}
}

FGameplayTag FAuraGameplayTags::GetGameplayTagByAttributeType(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayTag* Target = Ins.AttributesTagMapData.Find(InAttributeType))
	{
		return *Target;
	}

	return FGameplayTag();
}
