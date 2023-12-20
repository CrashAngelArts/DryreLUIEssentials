// Copyright © 2024 - DryreL Design

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralStructures.h"

#include "HAL/Platform.h"
#include <stdlib.h>
#include <stddef.h>

#if PLATFORM_WINDOWS

THIRD_PARTY_INCLUDES_START
#include "Windows/WindowsHWrapper.h"
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

	UFUNCTION()
	static bool IsMacPlatform();

	UFUNCTION()
	static bool IsLinuxPlatform();

	UFUNCTION()
	static bool IsIOSPlatform();

	UFUNCTION()
	static bool IsAndroidPlatform();

	UFUNCTION()
	static bool IsConsolePlatform();

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
	static int GetLaptopBatteryLevel();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetOperatingSystemBit();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsOperatingSystem64Bit();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsTouchscreenSupported();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsGamepadConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsMouseConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsCapslockActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsRunningOnLaptopBattery();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool RestartApplication();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetMaxRefreshRate();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetOSVersion();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool SupportsBrightness();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static float GetBrightness();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void SetBrightness(float Value);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FProcessInfo GetProcessInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FDeviceInfo GetDeviceInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FMonitorsInfo GetMonitorInformation();
	
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static bool SetActiveDisplay(int32 DisplayIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetDisplayCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static TArray<FDisplayInfo> GetAllDisplays();
};
