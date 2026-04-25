// Copyright NineForce Entertainment

#include "AuraGASEnumManager.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

void FAuraGASEnumManager::Init()
{
	FAuraGASEnumManager& Self = Get();
	Self.InternalInitForAttributes();
	Self.InternalInitForInputTags();
}

const FGameplayTag& FAuraGASEnumManager::GetAttributeGameplayTagByEnum(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayTag* Target = Get().AttributeEnumToTagMapData.Find(InAttributeType))
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

	return Get().InvalidGameplayTag;
}

const FGameplayTag& FAuraGASEnumManager::GetInputGameplayTagByEnum(EAuraInputTypes InType)
{
	if (auto TargetTag = Get().InputEnumToTagMapData.Find(InType))
	{
		return *TargetTag;
	}

	return Get().InvalidGameplayTag;
}

FGameplayAttribute FAuraGASEnumManager::GetGameplayAttributeByEnum(EAuraAttributeTypes InAttributeType)
{
	if (FGameplayAttribute* Target = Get().AttributeEnumToGAMapData.Find(InAttributeType))
	{
		return *Target;
	}

	return FGameplayAttribute();
}

EAuraAttributeTypes FAuraGASEnumManager::GetAttributeEnum(const FGameplayAttribute& InAttributeType)
{
	if (auto TargetEnum = Get().AttributeToAttriEnumMapData.Find(InAttributeType))
	{
		return *TargetEnum;
	}

	return EAuraAttributeTypes::None;
}

void FAuraGASEnumManager::InternalInitForAttributes()
{
	FAuraGASEnumManager& Self        = Get();
	UEnum*               TargetSEnum = StaticEnum<EAuraAttributeTypes>();
	Self.AttributeEnumToTagMapData.Reset();
	Self.AttributeEnumToGAMapData.Reset();
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
		Self.AttributeEnumToGAMapData.Add(TargetEnum, TargetAttribute);
		Self.AttributeToAttriEnumMapData.Add(TargetAttribute, TargetEnum);

		// 注册 GameplayTags
		{
			auto TargetEnumIndex = TargetSEnum->GetIndexByValue(TargetEnumValue);
			auto Importance      = TargetSEnum->GetMetaData(TEXT("Importance"), TargetEnumIndex);
			checkf(
				!Importance.IsEmpty(),
				TEXT("Enum : %s no Importance MetaData, Please check"),
				*TargetSEnum->GetAuthoredNameStringByIndex(TargetEnumIndex)
			);

			auto    TagDevComment = TargetSEnum->GetMetaData(TEXT("TagDevComment"), TargetEnumIndex);
			FString TagName       = FString::Printf(
				TEXT("Attributes.%s.%s"),
				*Importance,
				*TargetSEnum->GetAuthoredNameStringByIndex(TargetEnumIndex)
			);
			FGameplayTag TargetTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
				FName(TagName),
				TagDevComment
			);

			check(TargetTag.IsValid());

			Self.AttributeEnumToTagMapData.Add(
				static_cast<EAuraAttributeTypes>(TargetEnumValue),
				TargetTag
			);
		}
	}

	for (int Index = 1; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		const FGameplayTag* FindTarget = Self.AttributeEnumToTagMapData.Find(
			static_cast<EAuraAttributeTypes>(TargetSEnum->GetValueByIndex(Index))
		);

		checkf(
			FindTarget,
			TEXT("Attribute 枚举：%s，没有对应的 Attribute 成员变量，请检查！"),
			*TargetSEnum->GetNameByIndex(Index).ToString()
		);
	}
}

void FAuraGASEnumManager::InternalInitForInputTags()
{
	auto TargetSEnum = StaticEnum<EAuraInputTypes>();
	for (int Index = 0; Index < TargetSEnum->NumEnums() - 1; ++Index)
	{
		auto    TargetEnumValue = TargetSEnum->GetValueByIndex(Index);
		auto    TagDevComment   = TargetSEnum->GetMetaData(TEXT("TagDevComment"), Index);
		FString TagName         = FString::Printf(
			TEXT("Input.%s"),
			*TargetSEnum->GetAuthoredNameStringByIndex(Index)
		);
		FGameplayTag TargetTag = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName(TagName),
			TagDevComment
		);

		check(TargetTag.IsValid());

		Get().InputEnumToTagMapData.Add(
			static_cast<EAuraInputTypes>(TargetEnumValue),
			TargetTag
		);
	}
}
