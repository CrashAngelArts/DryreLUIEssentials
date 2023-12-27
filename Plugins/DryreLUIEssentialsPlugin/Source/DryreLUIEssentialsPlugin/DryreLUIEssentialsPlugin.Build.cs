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
				//"DryreLUIEssentialsPlugin",
				// ... add private dependencies that you statically link with here ...	
			}
			);

			if ((Target.IsInPlatformGroup(UnrealPlatformGroup.Windows)))
			{
			
			// Add path to plugin
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "include")); // Header Files
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "generate_library")); // Header Files
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "lib")); // Library Files (Static)
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "dll", "Release")); // Library Files (Dynamic)
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "ADL", "ADLXHelper", "Windows", "Cpp")); // Header Files

			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "include")); // Header Files
            PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "generate_library")); // Header Files
            PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "lib")); // Library Files (Static)
			PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source", "ThirdParty", "NVML", "dll", "Release")); // Library Files (Dynamic)

			// Uses DXGI to query GPU hardware
			// This is what will allow us to get GPU usage statistics at runtime (example: GPU VRAM values)
			PublicSystemLibraries.Add("DXGI.lib");
			
			// STATIC LIBRARY
			// NOTE: Disabled because dynamic library is required to load/unload these libraries depending on the GPU Brand.
			// NVML Library is used to get NVIDIA GPU functions
			//PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/NVML/lib/nvml.lib");
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/NVML/lib/nvml.lib");
			// ADL Library is used to get AMD GPU functions
			//PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/ADL/lib/PerfAllMetrics.lib");
			PublicAdditionalLibraries.Add("$(PluginDir)/Source/ThirdParty/ADL/lib/PerfAllMetrics.lib");
			
			// DYNAMIC LIBRARY
			// NVML Library is used to get NVIDIA GPU functions
			PublicDelayLoadDLLs.Add("$(PluginDir)/Source/ThirdParty/NVML/dll/Release/NVMLManager.dll");
			// ADL Library is used to get AMD GPU functions
			PublicDelayLoadDLLs.Add("$(PluginDir)/Source/ThirdParty/ADL/dll/Release/ADLManager.dll");

			}
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
				
			}
			);
	}
}
