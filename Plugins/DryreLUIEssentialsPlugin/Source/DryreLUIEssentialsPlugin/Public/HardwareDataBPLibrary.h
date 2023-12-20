// Copyright © 2024 - DryreL Design

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralStructures.h"
#include "Windows/WindowsHWrapper.h"

#include "HAL/Platform.h"
#include <stdlib.h>
#include <stddef.h>

#if PLATFORM_WINDOWS

THIRD_PARTY_INCLUDES_START
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "dxgi1_4.h"
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Shlwapi.h>
THIRD_PARTY_INCLUDES_END

#endif


#include "HardwareDataBPLibrary.generated.h"

UCLASS()
class UHardwareDataBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	
	UFUNCTION()
	static bool IsWindowsPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FCPUInfo GetCPUInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static float GetCPUUsage();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FGPUInfo GetGPUInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FMemInfo GetMemoryInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FOSInfo GetOSInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsGamepadConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsMouseConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsCapslockActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FProcessInfo GetProcessInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FDeviceInfo GetDeviceInformation();
};
