// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "AuraAttributeAssetActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class AURAEDITOR_API UAuraAttributeAssetActionUtility : public UAssetActionUtility
{
	GENERATED_BODY()
public:
	UAuraAttributeAssetActionUtility();
	
	UFUNCTION(CallInEditor)
	void FillAuraAttributeInfoData();
};
