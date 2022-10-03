// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GreenGuy : ModuleRules
{
	public GreenGuy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "NavigationSystem", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		//if (Target.bBuildEditor)
		//{
		//	PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		//}

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
