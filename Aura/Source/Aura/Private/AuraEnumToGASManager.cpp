// Copyright NineForce Entertainment

#include "AuraEnumToGASManager.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

void FAuraEnumToGASManager::Init()
{
	auto                   TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	FAuraEnumToGASManager& Self        = Get();
	Self.EnumToTagMapData.Reset();
	Self.EnumToAttributeMapData.Reset();
	for (TFieldIterator<FProperty> It(UAuraAttributeSet::StaticClass()); It; ++It)
	{
		FProperty* Property = *It;

		// 看是不是 struct
		FStructProperty* StructProp = CastField<FStructProperty>(Property);
		if (StructProp == nullptr)
		{
			continue;
		}

		// 看这个 struct 是不是 FGameplayAttributeData
		if (StructProp->Struct != TBaseStructure<FGameplayAttributeData>::Get())
		{
			continue;
		}

		auto TargetEnumValue = TargetSEnum->GetValueByName(FName(StructProp->GetName()));
		checkf(
			TargetEnumValue != INDEX_NONE,
			TEXT("AttributeSet 成员 在 EAuraAttributeTypes 里面没有对应枚举值，成员名字:%s"),
			*StructProp->Struct.GetName()
		);

		Self.EnumToAttributeMapData.Add(static_cast<EAuraAttributeTypes>(TargetEnumValue), FGameplayAttribute(Property));

		// 注册 GameplayTags
		{
			auto TargetEnumIndex = TargetSEnum->GetIndexByValue(TargetEnumValue);
			auto Importance      = TargetSEnum->GetMetaData(TEXT("Importance"), TargetEnumIndex);
			checkf(
				!Importance.IsEmpty(),
				TEXT("Enum : %s no Importance MetaData, Please check"),
				*TargetSEnum->GetAuthoredNameStringByIndex(TargetEnumIndex)
			);

			auto TagDevComment = TargetSEnum->GetMetaData(TEXT("TagDevComment"), TargetEnumIndex);

			FString TagName = FString::Printf(
				TEXT("Attributes.%s.%s"),
				*Importance,
				*TargetSEnum->GetAuthoredNameStringByIndex(TargetEnumIndex)
			);

			FName        FinalName(TagName);
			FGameplayTag TargetTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FinalName,
				TagDevComment
			);
			if (TargetTag.IsValid())
			{
				Self.EnumToTagMapData.Add(
					static_cast<EAuraAttributeTypes>(TargetEnumValue),
					TargetTag
				);
			}
		}
	}

	for (int Index = 0; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		const FGameplayTag* FindTarget = Self.EnumToTagMapData.Find(
			static_cast<EAuraAttributeTypes>(TargetSEnum->GetValueByIndex(Index))
		);

		if (FindTarget == nullptr)
		{
			UE_LOG(
				LogTemp,
				Error,
				TEXT("Attribute 枚举：%s，没有对应的 Attribute 成员变量，请检查！"),
				*TargetSEnum->GetNameByIndex(Index).ToString()
			);
		}
	}
}

FGameplayTag FAuraEnumToGASManager::GetGameplayTagByAttributeType(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayTag* Target = Get().EnumToTagMapData.Find(InAttributeType))
	{
		return *Target;
	}

	return FGameplayTag();
}
