// Copyright © 2024 - DryreL Design

#include "DryreLUIEssentialsBPLibrary.h"

#include "DSP/LFO.h"
#include "GenericPlatform/GenericApplication.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GenericPlatform/GenericPlatformTime.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformDriver.h"
#include "Framework/Application/SlateApplication.h"
#include "GameFramework/GameUserSettings.h"

#include "Kismet/GameplayStatics.h"

UDryreLUIEssentialsBPLibrary::UDryreLUIEssentialsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

bool UDryreLUIEssentialsBPLibrary::IsWindowsPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Windows") ? true : false;
}

bool UDryreLUIEssentialsBPLibrary::IsMacPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Mac") ? true : false;
}

bool UDryreLUIEssentialsBPLibrary::IsLinuxPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Linux") ? true : false;
}

bool UDryreLUIEssentialsBPLibrary::IsIOSPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("IOS") ? true : false;
}

bool UDryreLUIEssentialsBPLibrary::IsAndroidPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Android") ? true : false;
}

bool UDryreLUIEssentialsBPLibrary::IsConsolePlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("consoles") ? true : false;
}

FCPUInfo UDryreLUIEssentialsBPLibrary::GetCPUInformation()
{
	FCPUInfo CPUInformation;

	if(IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get CPU Informations."));
		CPUInformation.CPUBrand = FWindowsPlatformMisc::GetCPUBrand();
		CPUInformation.CPUChipset = FWindowsPlatformMisc::GetCPUChipset();
		CPUInformation.CPUCores = FWindowsPlatformMisc::NumberOfCores();
		CPUInformation.CPUVendor = FWindowsPlatformMisc::GetCPUVendor();
		CPUInformation.CPUCoresWithHyperthread = FWindowsPlatformMisc::NumberOfCoresIncludingHyperthreads();
		CPUInformation.CPUUsage = FWindowsPlatformTime::GetCPUTime().CPUTimePct;
		CPUInformation.isINTEProcessor = IsNVIDIAGraphicsCard();
		CPUInformation.isAMDProcessor = IsAMDGraphicsCard();
		CPUInformation.isOTHERProcessor = IsINTELGraphicsCard();
		return CPUInformation;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic Platform libraries to detect CPU Informations."));
		CPUInformation.CPUBrand = FGenericPlatformMisc::GetCPUBrand();
		CPUInformation.CPUChipset = FGenericPlatformMisc::GetCPUChipset();
		CPUInformation.CPUCores = FGenericPlatformMisc::NumberOfCores();
		CPUInformation.CPUVendor = FGenericPlatformMisc::GetCPUVendor();
		CPUInformation.CPUCoresWithHyperthread = FGenericPlatformMisc::NumberOfCoresIncludingHyperthreads();
		CPUInformation.CPUUsage = FGenericPlatformTime::GetCPUTime().CPUTimePct;
		CPUInformation.isINTEProcessor = IsNVIDIAGraphicsCard();
		CPUInformation.isAMDProcessor = IsAMDGraphicsCard();
		CPUInformation.isOTHERProcessor = IsINTELGraphicsCard();
		return CPUInformation;
	}
	return CPUInformation;
}

float UDryreLUIEssentialsBPLibrary::GetCPUUsage()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformTime::GetCPUTime().CPUTimePct;
	}
	else
	{
		return FGenericPlatformTime::GetCPUTime().CPUTimePct;
	}
}

FGPUInfo UDryreLUIEssentialsBPLibrary::GetGPUInformation()
{
	FGPUInfo GPUInformation;
	int convertToMB = 1000 * 1000;

	IDXGIFactory4* pFactory;
	CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&pFactory);

	IDXGIAdapter3* adapter;
	pFactory->EnumAdapters(0, reinterpret_cast<IDXGIAdapter**>(&adapter));

	DXGI_QUERY_VIDEO_MEMORY_INFO videoMemoryInfo;
	adapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &videoMemoryInfo);

	int32 currentVRAM = videoMemoryInfo.CurrentUsage / convertToMB;
	int32 totalVRAM = videoMemoryInfo.Budget / convertToMB;
	int32 reservedCurrentVRAM = videoMemoryInfo.CurrentReservation / convertToMB;
	int32 reservedAvailableVRAM = videoMemoryInfo.AvailableForReservation / convertToMB;
	
	if(IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get GPU Informations."));
		GPUInformation.PrimaryGPUBrand = FWindowsPlatformMisc::GetPrimaryGPUBrand();
		GPUInformation.DeviceDescription = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).DeviceDescription;
		GPUInformation.ProviderName = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).ProviderName;
		GPUInformation.AvailableVRAM = ((totalVRAM)-(currentVRAM));
		GPUInformation.CurrentVRAM = currentVRAM;
		GPUInformation.TotalVRAM = totalVRAM;
		GPUInformation.ReservedCurrentVRAM = reservedCurrentVRAM;
		GPUInformation.ReservedAvailableVRAM = reservedAvailableVRAM;
		GPUInformation.InternalDriverVersion = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).InternalDriverVersion;
		GPUInformation.UserDriverVersion = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).UserDriverVersion;
		GPUInformation.DriverDate = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).DriverDate;
		GPUInformation.RHIName = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).RHIName;
		GPUInformation.isNVIDIAGraphicsCard = IsNVIDIAGraphicsCard();
		GPUInformation.isAMDGraphicsCard = IsAMDGraphicsCard();
		GPUInformation.isINTELGraphicsCard = IsINTELGraphicsCard();
		GPUInformation.isOTHERGraphicsCard = IsOtherGraphicsCard();
		return GPUInformation;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get CPU Informations."));
		GPUInformation.PrimaryGPUBrand = FGenericPlatformMisc::GetPrimaryGPUBrand();
		GPUInformation.DeviceDescription = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).DeviceDescription;
		GPUInformation.ProviderName = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).ProviderName;
		GPUInformation.InternalDriverVersion = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).InternalDriverVersion;
		GPUInformation.UserDriverVersion = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).UserDriverVersion;
		GPUInformation.DriverDate = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).DriverDate;
		GPUInformation.RHIName = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).RHIName;
		GPUInformation.isNVIDIAGraphicsCard = IsNVIDIAGraphicsCard();
		GPUInformation.isAMDGraphicsCard = IsAMDGraphicsCard();
		GPUInformation.isINTELGraphicsCard = IsINTELGraphicsCard();
		GPUInformation.isOTHERGraphicsCard = IsOtherGraphicsCard();
		return GPUInformation;
	}
	return GPUInformation;
}

FMemInfo UDryreLUIEssentialsBPLibrary::GetMemoryInformation()
{
	FMemInfo MemoryInformation;
	int32 convertByteToMB = 1000 * 1000;
	
	if(IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get Memory Informations."));
		MemoryInformation.TotalPhysicalMemoryInGB = FWindowsPlatformMemory::GetPhysicalGBRam();
		MemoryInformation.PhysicalMemoryAvailableInMB = FWindowsPlatformMemory::GetStats().AvailablePhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryAvailableInMB = FWindowsPlatformMemory::GetStats().AvailableVirtual / convertByteToMB;
		MemoryInformation.PhysicalMemoryUsedInMB = FWindowsPlatformMemory::GetStats().UsedPhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryUsedInMB = FWindowsPlatformMemory::GetStats().UsedVirtual / convertByteToMB;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get Memory Informations."));
		MemoryInformation.TotalPhysicalMemoryInGB = FGenericPlatformMemory::GetPhysicalGBRam() / 1000;
		MemoryInformation.PhysicalMemoryAvailableInMB = FGenericPlatformMemory::GetStats().AvailablePhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryAvailableInMB = FGenericPlatformMemory::GetStats().AvailableVirtual / convertByteToMB;
		MemoryInformation.PhysicalMemoryUsedInMB = FGenericPlatformMemory::GetStats().UsedPhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryUsedInMB = FGenericPlatformMemory::GetStats().UsedVirtual / convertByteToMB;
	}
	return MemoryInformation;
}

FOSInfo UDryreLUIEssentialsBPLibrary::GetOSInfo()
{
	FOSInfo OSInformation;
	if (IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get OS Informations."));
		OSInformation.ComputerName = FWindowsPlatformProcess::ComputerName();
		OSInformation.Username = FWindowsPlatformProcess::UserName();
		OSInformation.LaptopBatteryLevel = FWindowsPlatformMisc::GetBatteryLevel();
		OSInformation.IsRunningOnLaptopBattery = FWindowsPlatformMisc::IsRunningOnBattery();
		OSInformation.OperatingSystemBit = GetOperatingSystemBit();
		OSInformation.IsOperatingSystem64Bit = FWindowsPlatformMisc::Is64bitOperatingSystem();
		OSInformation.IsDesktopTouchScreen = FWindowsPlatformMisc::DesktopTouchScreen();
		OSInformation.IsHDRUsedByDefault = FWindowsPlatformMisc::UseHDRByDefault();
		OSInformation.IsGamepadConnected = GetIsGamepadConnected();
		OSInformation.IsMouseConnected = GetIsMouseConnected();
		OSInformation.IsCapsLockActive = GetIsCapslockActive();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get OS Informations."));
		OSInformation.ComputerName = FGenericPlatformProcess::ComputerName();
		OSInformation.Username = FGenericPlatformProcess::UserName();
		OSInformation.LaptopBatteryLevel = FGenericPlatformMisc::GetBatteryLevel();
		OSInformation.IsRunningOnLaptopBattery = FGenericPlatformMisc::IsRunningOnBattery();
		OSInformation.OperatingSystemBit = GetOperatingSystemBit();
		OSInformation.IsOperatingSystem64Bit = FGenericPlatformMisc::Is64bitOperatingSystem();
		OSInformation.IsDesktopTouchScreen = FGenericPlatformMisc::DesktopTouchScreen();
		OSInformation.IsHDRUsedByDefault = FGenericPlatformMisc::UseHDRByDefault();
		OSInformation.IsGamepadConnected = GetIsGamepadConnected();
		OSInformation.IsMouseConnected = GetIsMouseConnected();
		OSInformation.IsCapsLockActive = GetIsCapslockActive();
	}
	return OSInformation;
}

int UDryreLUIEssentialsBPLibrary::GetLaptopBatteryLevel()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::GetBatteryLevel();
	}
	else
	{
		return FGenericPlatformMisc::GetBatteryLevel();
	}
}

FString UDryreLUIEssentialsBPLibrary::GetOperatingSystemBit()
{
	if(IsWindowsPlatform())
	{
		if(FWindowsPlatformMisc::Is64bitOperatingSystem())
		{
			return ("64-bit");
		}
		else
		{
			return ("32-bit");
		}
	}
	else
	{
		if(FGenericPlatformMisc::Is64bitOperatingSystem())
		{
			return ("64-bit");
		}
		else
		{
			return ("32-bit");
		}
	}
}

bool UDryreLUIEssentialsBPLibrary::GetIsOperatingSystem64Bit()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::Is64bitOperatingSystem();
	}
	else
	{
		return FGenericPlatformMisc::Is64bitOperatingSystem();
	}
}

bool UDryreLUIEssentialsBPLibrary::GetIsTouchscreenSupported()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::DesktopTouchScreen();
	}
	else
	{
		return FGenericPlatformMisc::DesktopTouchScreen();
	}
}

bool UDryreLUIEssentialsBPLibrary::GetIsGamepadConnected()
{
	const auto GamepadDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (GamepadDetectApplication.Get() != nullptr && GamepadDetectApplication->IsGamepadAttached())
	{
		return true;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::GetIsMouseConnected()
{
	const auto MouseDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (MouseDetectApplication.Get() != nullptr && MouseDetectApplication->IsMouseAttached())
	{
		return true;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::GetIsCapslockActive()
{
	const auto CapslockDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (CapslockDetectApplication.Get() != nullptr && CapslockDetectApplication->GetModifierKeys().AreCapsLocked())
	{
		return true;
	}
	return false;
}

int UDryreLUIEssentialsBPLibrary::GetMaxRefreshRate()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::GetMaxRefreshRate();
	}
	else
	{
		return FGenericPlatformMisc::GetMaxRefreshRate();
	}
}

FString UDryreLUIEssentialsBPLibrary::GetOSVersion()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::GetOSVersion();
	}
	else
	{
		return FGenericPlatformMisc::GetOSVersion();
	}
}

bool UDryreLUIEssentialsBPLibrary::GetIsRunningOnLaptopBattery()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::IsRunningOnBattery();
	}
	else
	{
		return FGenericPlatformMisc::IsRunningOnBattery();
	}
}

bool UDryreLUIEssentialsBPLibrary::GetRestartApplication()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::RestartApplication();
	}
	else
	{
		return FGenericPlatformMisc::RestartApplication();
	}
}

bool UDryreLUIEssentialsBPLibrary::GetSupportsBrightness()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::SupportsBrightness();
	}
	else
	{
		return FGenericPlatformMisc::SupportsBrightness();
	}
}

float UDryreLUIEssentialsBPLibrary::GetBrightness()
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::GetBrightness();
	}
	else
	{
		return FGenericPlatformMisc::GetBrightness();
	}
}

void UDryreLUIEssentialsBPLibrary::SetBrightness(float Value)
{
	if(IsWindowsPlatform())
	{
		return FWindowsPlatformMisc::SetBrightness(Value);
	}
	else
	{
		return FGenericPlatformMisc::SetBrightness(Value);
	}
}

FProcessInfo UDryreLUIEssentialsBPLibrary::GetProcessInformation()
{
	FProcessInfo ProcessInformation;
	if (IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get Process Informations."));
		ProcessInformation.ProcessID = FWindowsPlatformProcess::GetCurrentProcessId();
		ProcessInformation.ApplicationDirectory = FWindowsPlatformProcess::GetApplicationName(FWindowsPlatformProcess::GetCurrentProcessId());
		ProcessInformation.IsFirstInstance = FWindowsPlatformProcess::IsFirstInstance();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get Process Informations."));
		ProcessInformation.ProcessID = FGenericPlatformProcess::GetCurrentProcessId();
		ProcessInformation.ApplicationDirectory = FGenericPlatformProcess::GetApplicationName(FGenericPlatformProcess::GetCurrentProcessId());
		ProcessInformation.IsFirstInstance = FGenericPlatformProcess::IsFirstInstance();
	}
	return ProcessInformation;
}

FDeviceInfo UDryreLUIEssentialsBPLibrary::GetDeviceInformation()
{
	FDeviceInfo DeviceInformation;
	if (IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get Device Informations."));
		
		DeviceInformation.DeviceTemperature = FWindowsPlatformMisc::GetDeviceTemperatureLevel();
		
		#if PLATFORM_WINDOWS
			HRESULT hr = NULL;

			CoInitialize(NULL);
			IMMDeviceEnumerator *deviceEnumerator = NULL;
			hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (LPVOID *)&deviceEnumerator);
			IMMDevice *defaultDevice = NULL;

			hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
			deviceEnumerator->Release();
			deviceEnumerator = NULL;

			IAudioEndpointVolume *endpointVolume = NULL;
			hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL, (LPVOID *)&endpointVolume);
			defaultDevice->Release();
			defaultDevice = NULL;

			float currentVolume = 0;
			endpointVolume->GetMasterVolumeLevel(&currentVolume);
			endpointVolume->GetMasterVolumeLevelScalar(&currentVolume);
			endpointVolume->Release();
		
			DeviceInformation.DeviceVolume = currentVolume;
		#endif
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get Device Informations."));
		DeviceInformation.DeviceTemperature = FGenericPlatformMisc::GetDeviceTemperatureLevel();
		DeviceInformation.DeviceVolume = FGenericPlatformMisc::GetDeviceVolume();		
	}
	return DeviceInformation;
}

FMonitorsInfo UDryreLUIEssentialsBPLibrary::GetMonitorInformation()
{
	FMonitorsInfo MonitorInformation;

	UE_LOG(LogTemp, Log, TEXT("Using libraries to get Monitor Informations."));
	
		MonitorInformation.DisplayCount = GetDisplayCount();
		MonitorInformation.AllDisplays = GetAllDisplays();
		MonitorInformation.ActiveDisplay = GetActiveDisplay();
		MonitorInformation.ActiveDisplayIndex = GetActiveDisplayIndex();
		MonitorInformation.MaxRefreshRate = GetMaxRefreshRate();
	
	return MonitorInformation;
}

FString UDryreLUIEssentialsBPLibrary::GetLogin_ID()
{
	if (IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get Login ID."));
		return FWindowsPlatformMisc::GetLoginId();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get Login ID."));
		return FGenericPlatformMisc::GetLoginId();
	}
}

FString UDryreLUIEssentialsBPLibrary::GetTimeZone_ID()
{
	if (IsWindowsPlatform())
	{
		UE_LOG(LogTemp, Log, TEXT("Windows Platform Detected, using Windows libraries to get TimeZone ID."));
		return FWindowsPlatformMisc::GetTimeZoneId();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Using Generic libraries to get TimeZone ID."));
		return FGenericPlatformMisc::GetTimeZoneId();
	}
}

bool UDryreLUIEssentialsBPLibrary::SetActiveDisplay(int32 DisplayIndex)
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	if(DisplayIndex >= Displays.MonitorInfo.Num())
	{
		// Non existing display
		return false;
	}

#if !WITH_EDITOR
	const FMonitorInfo TargetMonitor = Displays.MonitorInfo[DisplayIndex];
	FVector2D WindowPosition(static_cast<float>(TargetMonitor.WorkArea.Left), static_cast<float>(TargetMonitor.WorkArea.Top));
	
	if (GEngine && GEngine->GameViewport)
	{
		// Display Switching
		TSharedPtr<SWindow> GWindow = GEngine->GameViewport->GetWindow();
		GWindow->MoveWindowTo(WindowPosition);

		// Switching resolution
		UGameUserSettings* UserSettings = GEngine->GameUserSettings;
		UserSettings->SetScreenResolution((FIntPoint(TargetMonitor.NativeWidth, TargetMonitor.NativeHeight)));
		UserSettings->ApplyResolutionSettings((false));
	}
#endif
	
	return true;
}

FDisplayInfo UDryreLUIEssentialsBPLibrary::GetActiveDisplay()
{
	TArray<FDisplayInfo> AllDisplays = GetAllDisplays();
	FDisplayInfo defaultStruct;

	for(FDisplayInfo oneDisplay:AllDisplays)
	{
		if(oneDisplay.bIsPrimary == true)
		{
			return oneDisplay;
			break;
		}
		return defaultStruct;
	}
	return defaultStruct;
}

int UDryreLUIEssentialsBPLibrary::GetActiveDisplayIndex()
{
	const TArray<FDisplayInfo> AllDisplays = GetAllDisplays();
	int activeDisplayIndex = -1;

	//AllDisplays.Find(oneDisplay);

	for(FDisplayInfo oneDisplay:AllDisplays)
	{
		if(oneDisplay.bIsPrimary == true)
		{
			activeDisplayIndex = AllDisplays.Find(oneDisplay);
			return activeDisplayIndex;
		}
		return activeDisplayIndex;
	}
	return activeDisplayIndex;
}

int UDryreLUIEssentialsBPLibrary::GetDisplayCount()
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);
	return Displays.MonitorInfo.Num();
}

TArray<FDisplayInfo> UDryreLUIEssentialsBPLibrary::GetAllDisplays()
{
	TArray<FDisplayInfo> AllDisplays;
	AllDisplays.Reset();

	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	for (const FMonitorInfo& Monitor : Displays.MonitorInfo)
	{
		AllDisplays.Add(FDisplayInfo(Monitor.Name, Monitor.ID, Monitor.NativeWidth, Monitor.NativeHeight, 
		Monitor.MaxResolution, Monitor.bIsPrimary, Monitor.DPI));
	}
	return AllDisplays;
}

bool UDryreLUIEssentialsBPLibrary::IsINTELProcessor()
{
	const bool bIsINTELCPUWindows = FWindowsPlatformMisc::GetCPUVendor().Contains(TEXT("GenuineIntel"));
	const bool bIsINTELCPUGeneric = FGenericPlatformMisc::GetCPUVendor().Contains(TEXT("GenuineIntel"));

	if(IsWindowsPlatform())
	{
		return bIsINTELCPUWindows;
	}
	else
	{
		return bIsINTELCPUGeneric;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsAMDProcessor()
{
	const bool bIsAMDCPUWindows = FWindowsPlatformMisc::GetCPUVendor().Contains(TEXT("AuthenticAMD"));
	const bool bIsAMDCPUGeneric = FGenericPlatformMisc::GetCPUVendor().Contains(TEXT("AuthenticAMD"));

	if(IsWindowsPlatform())
	{
		return bIsAMDCPUWindows;
	}
	else
	{
		return bIsAMDCPUGeneric;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsOtherProcessor()
{
	const bool bIsINTELCPUWindows = FWindowsPlatformMisc::GetCPUVendor().Contains(TEXT("GenuineIntel"));
	const bool bIsINTELCPUGeneric = FGenericPlatformMisc::GetCPUVendor().Contains(TEXT("GenuineIntel"));
	const bool bIsAMDCPUWindows = FWindowsPlatformMisc::GetCPUVendor().Contains(TEXT("AuthenticAMD"));
	const bool bIsAMDCPUGeneric = FGenericPlatformMisc::GetCPUVendor().Contains(TEXT("AuthenticAMD"));
	
	if(IsWindowsPlatform())
	{
		return (!bIsINTELCPUWindows && !bIsAMDCPUWindows) ? true : false;
	}
	else
	{
		return (!bIsINTELCPUGeneric && !bIsAMDCPUGeneric) ? true : false;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsNVIDIAGraphicsCard()
{
	//const bool gpuVendorWindows = FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("NVIDIA"));
	//const bool gpuVendorGeneric = FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("NVIDIA"));

	const bool gpuVendorWindows = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsNVIDIA();
	const bool gpuVendorGeneric = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsNVIDIA();

	if(IsWindowsPlatform())
	{
		if(gpuVendorWindows)
		{
		return true;
		}
		return false;
	}
	else
	{
		if(gpuVendorGeneric)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsINTELGraphicsCard()
{
	const bool gpuVendorWindows = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsIntel();
	const bool gpuVendorGeneric = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsIntel();
	
	if(IsWindowsPlatform())
	{
		if(gpuVendorWindows)
		{
			return true;
		}
		return false;
	}
	else
	{
		if(gpuVendorGeneric)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsAMDGraphicsCard()
{
	const bool gpuVendorWindows = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsAMD();
	const bool gpuVendorGeneric = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsAMD();
	
	//const bool gpuVendorWindows = FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("Advanced Micro Devices, Inc.")) || FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("AMD"));
	//const bool gpuVendorGeneric = FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("Advanced Micro Devices, Inc.")) || FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("AMD"));

	if(IsWindowsPlatform())
	{
		if(gpuVendorWindows)
		{
			return true;
		}
		return false;
	}
	else
	{
		if(gpuVendorGeneric)
		{
			return true;
		}
		return false;
	}
	return false;
}

bool UDryreLUIEssentialsBPLibrary::IsOtherGraphicsCard()
{
	/*
	const bool gpuVendorWindowsNVIDIA = FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("NVIDIA"));
	const bool gpuVendorGenericNVIDIA = FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("NVIDIA"));
	const bool gpuVendorWindowsAMD = FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("Advanced Micro Devices, Inc.")) || FWindowsPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("AMD"));
	const bool gpuVendorGenericAMD = FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("Advanced Micro Devices, Inc.")) || FGenericPlatformMisc::GetPrimaryGPUBrand().Contains(TEXT("AMD"));
	*/

	const bool gpuVendorWindowsNVIDIA = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsNVIDIA();
	const bool gpuVendorGenericNVIDIA = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsNVIDIA();
	const bool gpuVendorWindowsAMD = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsAMD();
	const bool gpuVendorGenericAMD = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsAMD();
	const bool gpuVendorWindowsINTEL = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).IsIntel();
	const bool gpuVendorGenericINTEL = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).IsIntel();
	
	if(IsWindowsPlatform())
	{
		if(!gpuVendorWindowsNVIDIA && !gpuVendorWindowsAMD && !gpuVendorWindowsINTEL)
		{
			return true;
		}
		return false;
	}
	else
	{
		if(!gpuVendorGenericNVIDIA && !gpuVendorGenericAMD && !gpuVendorWindowsINTEL)
		{
			return true;
		}
		return false;
	}
	return false;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Usage_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
	return nvGPUUtilizationNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_MemoryUsage_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvMemoryUtilizationNVML(Index);
	else return -1;
}


int UDryreLUIEssentialsBPLibrary::GetGPU_VRAM_NVML(int Index, E_VRAM_STATUS_NVML state)
 {
	if (IsNVIDIAGraphicsCard())
	{
		switch (state)
		{
		case E_VRAM_STATUS_NVML::Free:
			return nvGetGPUVRAMNVML(Index, E_NV_VRAM_STATUS_NVML::Free);
		case E_VRAM_STATUS_NVML::Used:
			return nvGetGPUVRAMNVML(Index, E_NV_VRAM_STATUS_NVML::Used);
		case E_VRAM_STATUS_NVML::Total:
			return nvGetGPUVRAMNVML(Index, E_NV_VRAM_STATUS_NVML::Total);
		default:
			// Handle unknown enum value
				return -1;
		}
	}
	else return -1;
 }

int UDryreLUIEssentialsBPLibrary::GetGPU_Voltage_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvGetGPUVoltageNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_ClockSpeed_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvGetGPUClockSpeedNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_VRAM_ClockSpeed_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvGetGPUVRAMClockSpeedNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Temperature_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
	return nvGetGPUTemperatureNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_TemperatureThreshold_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvGetGPUTemperatureThresholdNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::Get_GPU_Power_NVML(int Index)
{
	if(IsNVIDIAGraphicsCard())
		return nvGetGPUPowerNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_DeviceCount_NVML()
{
	if(IsNVIDIAGraphicsCard())
	return nvGPUDeviceCountNVML();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::Get_GPU_FansCount_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetNumFansNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::Get_GPU_CoresCount_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetNumGpuCoresNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Architecture_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetArchitectureNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_BAR1_Memory_Info_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetBAR1MemoryInfoNVML(Index);
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Board_ID_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetBoardIDNVML(Index);
	else return -1;
}

FString UDryreLUIEssentialsBPLibrary::GetGPU_Board_Part_Number_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetBoardPartNumberNVML(Index);
	else return "Unknown";
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Brand_Type_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUBrandTypeNVML(Index);
	else return -1;
}

FString UDryreLUIEssentialsBPLibrary::GetGPU_Brand_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUBrandNVML(Index);
	else return "Unknown";
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Get_Count_NVML()
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetCountNVML();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_GetMemoryBusWidth_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetMemoryBusWidthNVML(Index);
	else return -1;
}

FString UDryreLUIEssentialsBPLibrary::GetGPU_GetName_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetNameNVML(Index);
	else return "Unknown";
}

int UDryreLUIEssentialsBPLibrary::GetGPU_GetPCIE_Speed_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetPcieSpeedNVML(Index);
	else return -1;
}

FString UDryreLUIEssentialsBPLibrary::GetGPU_GetVBIOS_Version_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetVBIOSVersionNVML(Index);
	else return "Unknown";
}

int UDryreLUIEssentialsBPLibrary::GetGPU_GetCUDA_ComputeCapability_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetCudaComputeCapabilityNVML(Index);
	else return -1;
}

bool UDryreLUIEssentialsBPLibrary::GetGPU_CUDA_Availability_NVML(int Index)
{
	return nvGetGPUCudaAvailabilityNVML(Index);
}

FString UDryreLUIEssentialsBPLibrary::GetGPU_GetPowerState_NVML(int Index)
{
	if (IsNVIDIAGraphicsCard())
		return nvGetGPUGetPowerStateNVML(Index);
	else return "Unknown";
}

void UDryreLUIEssentialsBPLibrary::GPU_Initialize_NVML()
{
	if(IsNVIDIAGraphicsCard())
	nvGPUInitializeNVML();
}

bool UDryreLUIEssentialsBPLibrary::GPU_IsInitialized_NVML()
{
	if(IsNVIDIAGraphicsCard())
		return nvIsInitializedNVML();
	else return false;
}

void UDryreLUIEssentialsBPLibrary::GPU_Shutdown_NVML()
{
	if(IsNVIDIAGraphicsCard())
	nvGPUShutdownNVML();
}

void UDryreLUIEssentialsBPLibrary::GPU_Initialize_ADL()
{
	if(IsAMDGraphicsCard())
	InitializeADL();
}

bool UDryreLUIEssentialsBPLibrary::GPU_IsInitialized_ADL()
{
	if(IsAMDGraphicsCard())
		return IsInitializedADL();
	else return false;
}

void UDryreLUIEssentialsBPLibrary::GPU_Shutdown_ADL()
{
	if(IsAMDGraphicsCard())
	ShutdownADL();
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Usage_ADL()
{
	if(IsAMDGraphicsCard())
	return adlGetGPUUsageADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_ClockSpeed_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUClockSpeedADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_VRAM_ClockSpeed_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUVRAMClockSpeedADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_TimeStamps_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetTimeStampADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Temperature_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUTemperatureADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_HotspotTemperature_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUHotspotTemperatureADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Power_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUPowerADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_TotalBoardPower_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUTotalBoardPowerADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_IntakeTemperature_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUIntakeTemperatureADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_FanSpeedInRPM_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUFanSpeedInRPMADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_VRAM_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUVRAMADL();
	else return -1;
}

int UDryreLUIEssentialsBPLibrary::GetGPU_Voltage_ADL()
{
	if(IsAMDGraphicsCard())
		return adlGetGPUVoltageADL();
	else return -1;
}

/*
E_NV_VRAM_STATUS_NVML UDryreLUIEssentialsBPLibrary::EqualityEnum(E_VRAM_STATUS_NVML Enum)
{
	switch (Enum)
	{
	case E_VRAM_STATUS_NVML::Free:
		return E_NV_VRAM_STATUS_NVML::Free;
		
	case E_VRAM_STATUS_NVML::Total:
		return E_NV_VRAM_STATUS_NVML::Total;
		
	case E_VRAM_STATUS_NVML::Used:
		return E_NV_VRAM_STATUS_NVML::Used;
		
	default:
		return E_NV_VRAM_STATUS_NVML::Free;		
	}
	
}
*/