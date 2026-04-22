// Copyright NineForce Entertainment

#include "Util/Asset/AuraAttributeAssetActionUtility.h"

#include "AuraGameDefine.h"
#include "AbilitySystem/Data/AuraAttributeInfoDataAsset.h"
#include "UObject/SavePackage.h"

UAuraAttributeAssetActionUtility::UAuraAttributeAssetActionUtility()
{
	SupportedClasses.Add(UAuraAttributeInfoDataAsset::StaticClass());
}

void UAuraAttributeAssetActionUtility::FillAuraAttributeInfoData()
{
	// 1. 获取当前在内容浏览器中选中的资产
	TArray<FAssetData> SelectedAssets;
	GEditor->GetContentBrowserSelections(SelectedAssets);

	UEnum* TargetEnum = StaticEnum<EAuraAttributeTypes>();
	// 2. 遍历选中的资产
	for (const FAssetData& AssetData : SelectedAssets)
	{
		// 检查资产类型是否匹配
		if (AssetData.AssetClassPath != UAuraAttributeInfoDataAsset::StaticClass()->GetClassPathName())
		{
			continue;
		}

		// 3. 加载资产对象
		UAuraAttributeInfoDataAsset* DataAsset = Cast<UAuraAttributeInfoDataAsset>(AssetData.GetAsset());
		if (!DataAsset)
		{
			continue;
		}
		DataAsset->AuraAttributeInfos.Empty();
		for (int Index = 1; Index < TargetEnum->NumEnums() - 1; Index++)
		{
			FAuraAttributeInfoData NewData = FAuraAttributeInfoData();
			FString                TagName = FString::Printf(
				TEXT("Attributes.%s.%s"),
				*TargetEnum->GetMetaData(TEXT("Importance"), Index),
				*TargetEnum->GetAuthoredNameStringByIndex(Index)
			);

			NewData.AttributeTag = FGameplayTag::RequestGameplayTag(FName(TagName), true);
			if (!NewData.AttributeTag.IsValid())
			{
				continue;
			}
			FText TargetName             = FText::FromString(TargetEnum->GetAuthoredNameStringByIndex(Index));
			NewData.AttributeName        = TargetName;
			NewData.AttributeValue       = 0;
			NewData.AttributeDescription = FText::FromString(TargetEnum->GetMetaData(TEXT("TagDevComment"), Index));
			DataAsset->AuraAttributeInfos.Add(NewData);
		}

		// 5. 标记资产为“脏”，以便保存
		DataAsset->MarkPackageDirty();

		// 6. 提示用户保存
		FText SaveMessage = FText::Format(
			NSLOCTEXT("MyDataAssetTool", "SaveAsset", "DataAsset '{0}' has been modified. Do you want to save it?"),
			FText::FromString(DataAsset->GetName())
		);
		if (FMessageDialog::Open(EAppMsgType::YesNo, SaveMessage) == EAppReturnType::Yes)
		{
			// 保存资产
			FString PackageFileName = FPackageName::LongPackageNameToFilename(
				DataAsset->GetOutermost()->GetName(),
				FPackageName::GetAssetPackageExtension()
			);
			FSavePackageArgs SaveArgs;
			SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
			SaveArgs.SaveFlags     = SAVE_NoError;
			UPackage::SavePackage(DataAsset->GetOutermost(), DataAsset, *PackageFileName, SaveArgs);
		}
	}
}
