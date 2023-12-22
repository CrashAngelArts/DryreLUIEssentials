// Copyright © 2024 - DryreL Design

using System.IO;
using UnrealBuildTool;

public class DryreLUIEssentialsPlugin : ModuleRules
{
	public DryreLUIEssentialsPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"Runtime/RHI",
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", 
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"RHI",
				"Slate",
				"SlateCore",
				"ApplicationCore", // Required for monitor settings, FDisplayMetrics
				// ... add private dependencies that you statically link with here ...	
			}
			);

			if ((Target.IsInPlatformGroup(UnrealPlatformGroup.Windows)))
			{
			// Uses DXGI to query GPU hardware
			// This is what will allow us to get GPU usage statistics at runtime
			PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "ThirdParty"));

			PublicSystemLibraries.Add("DXGI.lib"); // Required for GPU VRAM values
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/NVML/lib/nvml.lib");
			}
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
