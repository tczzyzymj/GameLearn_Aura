// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraAttributeInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttributeValue = 0;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_API UAuraAttributeInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	FAuraAttributeInfoData FindAttributeInfoDataByTag(const FGameplayTag& InTag, bool bLogNotFound = false);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfoData> AuraAttributeInfos;
};
