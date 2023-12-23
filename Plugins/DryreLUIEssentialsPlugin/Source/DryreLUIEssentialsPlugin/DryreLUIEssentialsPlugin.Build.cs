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
				"DryreLUIEssentialsPlugin",
				// ... add private dependencies that you statically link with here ...	
			}
			);

			if ((Target.IsInPlatformGroup(UnrealPlatformGroup.Windows)))
			{
			
			// Add path to plugin
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "include"));
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "lib"));
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "dll"));
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "ADLXHelper", "Windows", "Cpp"));
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "include"));
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "lib"));

			// Uses DXGI to query GPU hardware
			// This is what will allow us to get GPU usage statistics at runtime (example: GPU VRAM values)
			PublicSystemLibraries.Add("DXGI.lib");
			
			// NVML Library is used to get NVIDIA GPU functions
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/NVML/lib/nvml.lib");
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/ADL/lib/PerfAllMetrics.lib");
			}
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
