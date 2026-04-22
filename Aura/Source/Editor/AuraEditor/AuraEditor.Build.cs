using UnrealBuildTool;

public class AuraEditor : ModuleRules
{
	public AuraEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Aura",        // 你的游戏模块
				"Blutility",   // AssetActionUtility
				"UnrealEd",    // GEditor
				"AssetTools",  // 可选，资产创建工具
				"GameplayTags" // 你代码中用到了 FGameplayTag
			}
		);

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", });
	}
}
