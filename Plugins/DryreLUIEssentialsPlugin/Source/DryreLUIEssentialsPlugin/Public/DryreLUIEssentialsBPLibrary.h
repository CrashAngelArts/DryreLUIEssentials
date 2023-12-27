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

#include "../Source/ThirdParty/NVML/generate_library/NVMLManager.h"
//#include "../Source/ThirdParty/NVML/generate_library/NVMLManager.cpp"
#include "../Source/ThirdParty/ADL/generate_library/ADLManager.h"
//#include "../Source/ThirdParty/ADL/generate_library/ADLManager.cpp"

//#include "NVMLManager.h"
//#include "ADLManager.h"
THIRD_PARTY_INCLUDES_END

#endif

#include "DryreLUIEssentialsBPLibrary.generated.h"

// Define an enum for VRAM STATUS
UENUM(BlueprintType)
enum class E_VRAM_STATUS_NVML : uint8 {
	Free,
	Used,
	Total
};

UCLASS()
class UDryreLUIEssentialsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	// Run Console Commands in C++
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void RunExec(APlayerController* PlayerController, FString Command);

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
	static float GetAverageFPS();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static float GetAverageMS();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetLogin_ID();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetTimeZone_ID();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetHasActiveWiFiConnection();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetLaptopBatteryLevel();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetOperatingSystemBit();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsOperatingSystem64Bit();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsTouchscreenSupported();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsGamepadConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsMouseConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsCapslockActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetIsRunningOnLaptopBattery();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetRestartApplication();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetMaxRefreshRate();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetOSVersion();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetSupportsBrightness();
	
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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static float GetGamma();
	
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void SetGamma(APlayerController* playerController, float Value = 2.2f);

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
	static int GetGPU_Usage_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_MemoryUsage_NVML(int Index);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_VRAM_NVML(int Index, E_VRAM_STATUS_NVML state);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
    static int GetGPU_Voltage_NVML(int Index);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_ClockSpeed_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_VRAM_ClockSpeed_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Temperature_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_TemperatureThreshold_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int Get_GPU_Power_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_DeviceCount_NVML();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int Get_GPU_FansCount_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int Get_GPU_CoresCount_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Architecture_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_BAR1_Memory_Info_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Board_ID_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetGPU_Board_Part_Number_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Brand_Type_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetGPU_Brand_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_MemoryBusWidth_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetGPU_Name_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_PCIE_Speed_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetGPU_VBIOS_Version_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_CUDA_ComputeCapability_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GetGPU_CUDA_Availability_NVML(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static FString GetGPU_PowerState_NVML(int Index);

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Initialize_NVML();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GPU_IsInitialized_NVML();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Shutdown_NVML();

	// ADLX Library (AMD Graphics Card)
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Initialize_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GPU_IsInitialized_ADL();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Shutdown_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Usage_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_DeviceCount_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_ClockSpeed_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_VRAM_ClockSpeed_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetSystem_TimeStamps_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Temperature_ADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_HotspotTemperature_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Power_ADL();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_TotalBoardPower_ADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_IntakeTemperature_ADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_FanSpeedInRPM_ADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_VRAM_ADL();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Voltage_ADL();

	// EqualityEnum (no more need)
	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	//static E_NV_VRAM_STATUS_NVML EqualityEnum(E_VRAM_STATUS_NVML Enum);

	// AUTO Library (AUTO SELECTS the used Graphics Card's function)
	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Initialize_AUTO();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static bool GPU_IsInitialized_AUTO();

	UFUNCTION(BlueprintCallable, Category = "Dryrel Design")
	static void GPU_Shutdown_AUTO();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Usage_AUTO(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_DeviceCount_AUTO();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_ClockSpeed_AUTO(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_VRAM_ClockSpeed_Auto(int Index);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Temperature_AUTO(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Power_AUTO(int Index);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_FanSpeed_AUTO(int Index);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Dryrel Design")
	static int GetGPU_Voltage_AUTO(int Index);
};