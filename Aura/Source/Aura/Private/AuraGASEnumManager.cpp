// Copyright NineForce Entertainment

#include "AuraGASEnumManager.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

void FAuraGASEnumManager::Init()
{
	UEnum*               TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	FAuraGASEnumManager& Self        = Get();
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

		auto TargetAttribute = FGameplayAttribute(Property);
		auto TargetEnum      = static_cast<EAuraAttributeTypes>(TargetEnumValue);
		Self.EnumToAttributeMapData.Add(TargetEnum, TargetAttribute);
		Self.AttributeToEnumMapData.Add(TargetAttribute, TargetEnum);

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

			check(TargetTag.IsValid());

			Self.EnumToTagMapData.Add(
				static_cast<EAuraAttributeTypes>(TargetEnumValue),
				TargetTag
			);
		}
	}

	for (int Index = 1; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		const FGameplayTag* FindTarget = Self.EnumToTagMapData.Find(
			static_cast<EAuraAttributeTypes>(TargetSEnum->GetValueByIndex(Index))
		);

		checkf(
			FindTarget,
			TEXT("Attribute 枚举：%s，没有对应的 Attribute 成员变量，请检查！"),
			*TargetSEnum->GetNameByIndex(Index).ToString()
		);
	}
}

FGameplayTag FAuraGASEnumManager::GetGameplayTagByEnum(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayTag* Target = Get().EnumToTagMapData.Find(InAttributeType))
	{
		return *Target;
	}
	
	// // 获取全局唯一的 GameplayTagsManager 实例
	// UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	//
	// // 构造你想查询的父标签，例如 "Attribute.A"
	// FGameplayTag ParentTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Primary"));
	//
	// // 获取包含该父标签所有子标签的容器（不含父标签自身）
	// FGameplayTagContainer ChildrenTags = TagManager.RequestGameplayTagChildren(ParentTag);
	//
	// // 现在可以遍历 ChildrenTags 来操作每个子标签
	// for (const FGameplayTag& Tag : ChildrenTags)
	// {
	// 	UE_LOG(LogTemp, Log, TEXT("Found child tag: %s"), *Tag.ToString());
	// }

	return FGameplayTag();
}

FGameplayAttribute FAuraGASEnumManager::GetGameplayAttributeByEnum(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayAttribute* Target = Get().EnumToAttributeMapData.Find(InAttributeType))
	{
		return *Target;
	}

	return FGameplayAttribute();
}

EAuraAttributeTypes FAuraGASEnumManager::GetAttributeEnum(const FGameplayAttribute& InAttributeType)
{
	if (auto TargetEnum = Get().AttributeToEnumMapData.Find(InAttributeType))
	{
		return *TargetEnum;
	}

	return EAuraAttributeTypes::None;
}
