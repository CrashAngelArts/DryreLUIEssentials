// Copyright © 2024 - DryreL Design

#include "DryreLUIEssentials.h"

#define LOCTEXT_NAMESPACE "FDryreLUIEssentialsPluginModule"

void FDryreLUIEssentialsPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
/*
	// Get the base directory of this plugin
	// Get a reference to the plugin manager
	FString BaseDir = IPluginManager::Get().FindPlugin("DryreLUIEssentialsPlugin")->GetBaseDir();

	if(IsRHIDeviceNVIDIA())
	{
		// Add on the relative location of the third party dll and load it
		FString LibraryPathNVML;
#if PLATFORM_WINDOWS
		LibraryPathNVML = FPaths::Combine(*BaseDir, TEXT("/Source/ThirdParty/NVML/dll/Release/NVMLManager.dll"));
#endif // PLATFORM_WINDOWS

		LibraryHandle = !LibraryPathNVML.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPathNVML) : nullptr;
	}
	else if(IsRHIDeviceAMD())
	{
		FString LibraryPathADL;
#if PLATFORM_WINDOWS
		LibraryPathADL = FPaths::Combine(*BaseDir, TEXT("/Source/ThirdParty/ADL/dll/Release/ADLManager.dll"));
#endif // PLATFORM_WINDOWS
		LibraryHandle = !LibraryPathADL.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPathADL) : nullptr;
	}

	if (LibraryHandle)
	{
		if(IsRHIDeviceNVIDIA())
		{
			nvGPUInitializeNVML();
		}
		else if(IsRHIDeviceAMD())
		{
			adlInitializeADL();
		}
		else if(IsRHIDeviceIntel())
		{
			
		}
		else if(IsRHIDeviceApple())
		{
			
		}
		else
		{
			
		}
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("DryreLUIEssentialsError", "Failed to load library"));
	}
	*/
}

void FDryreLUIEssentialsPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if(IsRHIDeviceNVIDIA())
	{
		nvGPUShutdownNVML();
	}
	else if(IsRHIDeviceAMD())
	{
		adlGPUShutdownADL();
	}
	else if(IsRHIDeviceIntel())
	{
			
	}
	else if(IsRHIDeviceApple())
	{
			
	}
	else
	{
			
	}

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(LibraryHandle);
	LibraryHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDryreLUIEssentialsPluginModule, DryreLUIEssentialsPlugin)