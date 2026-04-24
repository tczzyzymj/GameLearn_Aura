// Copyright NineForce Entertainment

#include "AuraAssetManager.h"

#include "AuraGASEnumManager.h"
#include "AbilitySystem/AuraAttributeSet.h"

UAuraAssetManager::UAuraAssetManager()
{
}

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* TargetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *TargetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGASEnumManager::Init();
}
