// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyBossRush : ModuleRules
{
	public MyBossRush(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
