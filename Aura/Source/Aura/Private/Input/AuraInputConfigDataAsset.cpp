// Copyright NineForce Entertainment

#include "Input/AuraInputConfigDataAsset.h"

const UInputAction* UAuraInputConfigDataAsset::FindInputActonByInputEnum(EAuraInputTypes InType, bool bLogIfNotFound)
{
	if (auto TargetData = AuraInputConfigMapData.Find(InType))
	{
		return TargetData->InputAction;
	}

	if (bLogIfNotFound)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("UAuraInputConfigDataAsset::FindInputActonByTag Not Found !  Enum is : %s"),
			*StaticEnum<EAuraInputTypes>()->GetNameByValue(static_cast<int64>(InType)).ToString()
		);
	}

	return nullptr;
}
