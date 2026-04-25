// Copyright NineForce Entertainment

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AuraGameDefine.h"
#include "Engine/DataAsset.h"
#include "AuraInputConfigDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAuraInputData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAuraInputTypes, FAuraInputData> AuraInputConfigMapData;

	const UInputAction* FindInputActonByInputEnum(EAuraInputTypes InType, bool bLogIfNotFound = true);
};
