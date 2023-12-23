// Copyright © 2024 - DryreL Design

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralStructures.h"

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
#include "NVMLManager.h"
#include "ADLManager.h"
THIRD_PARTY_INCLUDES_END

#endif

#include "DryreLUIEssentialsBPLibrary.generated.h"

UCLASS()
class UDryreLUIEssentialsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Platform Check
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsWindowsPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsMacPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsLinuxPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsIOSPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsAndroidPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsConsolePlatform();

	// Struct
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
	static FProcessInfo GetProcessInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FDeviceInfo GetDeviceInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FMonitorsInfo GetMonitorInformation();

	// Others
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
	
	// Monitor/Display
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static bool SetActiveDisplay(int32 DisplayIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FDisplayInfo GetActiveDisplay();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetActiveDisplayIndex();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetDisplayCount();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static TArray<FDisplayInfo> GetAllDisplays();

	// Check The CPU Brand (Graphics Card)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsINTELProcessor();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsAMDProcessor();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsOtherProcessor();

	// Check The GPU Brand (Graphics Card)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsNVIDIAGraphicsCard();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsINTELGraphicsCard();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsAMDGraphicsCard();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool IsOtherGraphicsCard();

	// NVML Library (NVIDIA Graphics Card)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUUsageNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetMemoryUsageNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUClockSpeedNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUVRAMClockSpeedNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUTemperatureNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUTemperatureThresholdNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUPowerNVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUDeviceCountNVML();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPUInitializeNVML();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static bool GPUIsInitializedNVML();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPUShutdownNVML();

	// ADLX Library (AMD Graphics Card)
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPUInitializeADL();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static bool GPUIsInitializedADL();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPUShutdownADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUUsageADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUClockSpeedADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUVRAMClockSpeedADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetTimeStampsADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUTemperatureADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUHotspotTemperatureADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUPowerADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUTotalBoardPowerADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUIntakeTemperatureADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUFanSpeedADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUVRAMADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPUVoltageADL();
};
