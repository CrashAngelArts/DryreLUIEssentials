// Copyright © 2024 - DryreL Design

#include "HardwareDataBPLibrary.h"

#include "GenericPlatform/GenericApplication.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GenericPlatform/GenericPlatformTime.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformDriver.h"
#include "Framework/Application/SlateApplication.h"
#include "GameFramework/GameUserSettings.h"

#include "Kismet/GameplayStatics.h"

UHardwareDataBPLibrary::UHardwareDataBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

bool UHardwareDataBPLibrary::IsWindowsPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Windows") ? true : false;
}

bool UHardwareDataBPLibrary::IsMacPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Mac") ? true : false;
}

bool UHardwareDataBPLibrary::IsLinuxPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Linux") ? true : false;
}

bool UHardwareDataBPLibrary::IsIOSPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("IOS") ? true : false;
}

bool UHardwareDataBPLibrary::IsAndroidPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Android") ? true : false;
}

bool UHardwareDataBPLibrary::IsConsolePlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("consoles") ? true : false;
}

FCPUInfo UHardwareDataBPLibrary::GetCPUInformation()
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
	}
	return CPUInformation;
}

float UHardwareDataBPLibrary::GetCPUUsage()
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

FGPUInfo UHardwareDataBPLibrary::GetGPUInformation()
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
		return GPUInformation;
	}
	else
	{
		GPUInformation.PrimaryGPUBrand = FGenericPlatformMisc::GetPrimaryGPUBrand();
		GPUInformation.DeviceDescription = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).DeviceDescription;
		GPUInformation.ProviderName = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).ProviderName;
		GPUInformation.InternalDriverVersion = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).InternalDriverVersion;
		GPUInformation.UserDriverVersion = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).UserDriverVersion;
		GPUInformation.DriverDate = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).DriverDate;
		GPUInformation.RHIName = FGenericPlatformMisc::GetGPUDriverInfo(FGenericPlatformMisc::GetPrimaryGPUBrand()).RHIName;
		return GPUInformation;
	}
}

FMemInfo UHardwareDataBPLibrary::GetMemoryInformation()
{
	FMemInfo MemoryInformation;
	int32 convertByteToMB = 1000 * 1000;
	
	if(IsWindowsPlatform())
	{
		MemoryInformation.TotalPhysicalMemoryInGB = FWindowsPlatformMemory::GetPhysicalGBRam();
		MemoryInformation.PhysicalMemoryAvailableInMB = FWindowsPlatformMemory::GetStats().AvailablePhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryAvailableInMB = FWindowsPlatformMemory::GetStats().AvailableVirtual / convertByteToMB;
		MemoryInformation.PhysicalMemoryUsedInMB = FWindowsPlatformMemory::GetStats().UsedPhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryUsedInMB = FWindowsPlatformMemory::GetStats().UsedVirtual / convertByteToMB;
	}
	else
	{
		MemoryInformation.TotalPhysicalMemoryInGB = FGenericPlatformMemory::GetPhysicalGBRam() / 1000;
		MemoryInformation.PhysicalMemoryAvailableInMB = FGenericPlatformMemory::GetStats().AvailablePhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryAvailableInMB = FGenericPlatformMemory::GetStats().AvailableVirtual / convertByteToMB;
		MemoryInformation.PhysicalMemoryUsedInMB = FGenericPlatformMemory::GetStats().UsedPhysical / convertByteToMB;
		MemoryInformation.VirtualMemoryUsedInMB = FGenericPlatformMemory::GetStats().UsedVirtual / convertByteToMB;
	}
	return MemoryInformation;
}

FOSInfo UHardwareDataBPLibrary::GetOSInfo()
{
	FOSInfo OSInformation;
	if (IsWindowsPlatform())
	{
		OSInformation.ComputerName = FWindowsPlatformProcess::ComputerName();
		OSInformation.Username = FWindowsPlatformProcess::UserName();
		OSInformation.LaptopBatteryLevel = FWindowsPlatformMisc::GetBatteryLevel();
		OSInformation.IsOperatingSystem64Bit = FWindowsPlatformMisc::Is64bitOperatingSystem();
		OSInformation.IsDesktopTouchScreen = FWindowsPlatformMisc::DesktopTouchScreen();
		OSInformation.IsHDRUsedByDefault = FWindowsPlatformMisc::UseHDRByDefault();
		OSInformation.IsGamepadConnected = IsGamepadConnected();
		OSInformation.IsMouseConnected = IsMouseConnected();
		OSInformation.IsCapsLockActive = IsCapslockActive();
	}
	else
	{
		OSInformation.ComputerName = FGenericPlatformProcess::ComputerName();
		OSInformation.Username = FGenericPlatformProcess::UserName();
		OSInformation.LaptopBatteryLevel = FGenericPlatformMisc::GetBatteryLevel();
		OSInformation.IsOperatingSystem64Bit = FGenericPlatformMisc::Is64bitOperatingSystem();
		OSInformation.IsDesktopTouchScreen = FGenericPlatformMisc::DesktopTouchScreen();
		OSInformation.IsHDRUsedByDefault = FGenericPlatformMisc::UseHDRByDefault();
		OSInformation.IsGamepadConnected = IsGamepadConnected();
		OSInformation.IsMouseConnected = IsMouseConnected();
		OSInformation.IsCapsLockActive = IsCapslockActive();
	}
	return OSInformation;
}

int UHardwareDataBPLibrary::GetLaptopBatteryLevel()
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

FString UHardwareDataBPLibrary::GetOperatingSystemBit()
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

bool UHardwareDataBPLibrary::IsOperatingSystem64Bit()
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

bool UHardwareDataBPLibrary::IsTouchscreenSupported()
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

bool UHardwareDataBPLibrary::IsGamepadConnected()
{
	const auto GamepadDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (GamepadDetectApplication.Get() != nullptr && GamepadDetectApplication->IsGamepadAttached())
	{
		return true;
	}
	return false;
}

bool UHardwareDataBPLibrary::IsMouseConnected()
{
	const auto MouseDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (MouseDetectApplication.Get() != nullptr && MouseDetectApplication->IsMouseAttached())
	{
		return true;
	}
	return false;
}

bool UHardwareDataBPLibrary::IsCapslockActive()
{
	const auto CapslockDetectApplication = FSlateApplication::Get().GetPlatformApplication();
	if (CapslockDetectApplication.Get() != nullptr && CapslockDetectApplication->GetModifierKeys().AreCapsLocked())
	{
		return true;
	}
	return false;
}

int UHardwareDataBPLibrary::GetMaxRefreshRate()
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

FString UHardwareDataBPLibrary::GetOSVersion()
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

bool UHardwareDataBPLibrary::IsRunningOnLaptopBattery()
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

bool UHardwareDataBPLibrary::RestartApplication()
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

bool UHardwareDataBPLibrary::SupportsBrightness()
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

float UHardwareDataBPLibrary::GetBrightness()
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

void UHardwareDataBPLibrary::SetBrightness(float Value)
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

FProcessInfo UHardwareDataBPLibrary::GetProcessInformation()
{
	FProcessInfo ProcessInformation;
	if (IsWindowsPlatform())
	{
		ProcessInformation.ProcessID = FWindowsPlatformProcess::GetCurrentProcessId();
		ProcessInformation.ApplicationName = FWindowsPlatformProcess::GetApplicationName(FWindowsPlatformProcess::GetCurrentProcessId());
		ProcessInformation.IsFirstInstance = FWindowsPlatformProcess::IsFirstInstance();
	}
	else
	{
		ProcessInformation.ProcessID = FGenericPlatformProcess::GetCurrentProcessId();
		ProcessInformation.ApplicationName = FGenericPlatformProcess::GetApplicationName(FGenericPlatformProcess::GetCurrentProcessId());
		ProcessInformation.IsFirstInstance = FGenericPlatformProcess::IsFirstInstance();
	}
	return ProcessInformation;
}

FDeviceInfo UHardwareDataBPLibrary::GetDeviceInformation()
{
	FDeviceInfo DeviceInformation;
	if (IsWindowsPlatform())
	{
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
		DeviceInformation.DeviceTemperature = FGenericPlatformMisc::GetDeviceTemperatureLevel();
		DeviceInformation.DeviceVolume = FGenericPlatformMisc::GetDeviceVolume();		
	}
	return DeviceInformation;
}

FMonitorsInfo UHardwareDataBPLibrary::GetMonitorInformation()
{
	FMonitorsInfo MonitorInformation;
	
		MonitorInformation.GetDisplayCount = GetDisplayCount();
		MonitorInformation.GetAllDisplays = GetAllDisplays();
	
	return MonitorInformation;
}

bool UHardwareDataBPLibrary::SetActiveDisplay(int32 DisplayIndex)
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);

	if(DisplayIndex > Displays.MonitorInfo.Num())
	{
		// Non existing display
		return false;
	}

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
		UserSettings->ApplyResolutionSettings((false);
	}
	
	return true;
}

int UHardwareDataBPLibrary::GetDisplayCount()
{
	FDisplayMetrics Displays;
	FDisplayMetrics::RebuildDisplayMetrics(Displays);
	return Displays.MonitorInfo.Num();
}

TArray<FDisplayInfo> UHardwareDataBPLibrary::GetAllDisplays()
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
