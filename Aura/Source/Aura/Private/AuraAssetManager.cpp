// Copyright NineForce Entertainment

#include "AuraAssetManager.h"

#include "AuraGameplayTags.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);
	UAuraAssetManager* TargetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *TargetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::InitNativeGameplayTags();
}
