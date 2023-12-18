// Copyright © 2024 - DryreL Design

#include "HardwareDataBPLibrary.h"

#include "GenericPlatform/GenericPlatformMisc.h"
#include "GenericPlatform/GenericPlatformTime.h"
#include "GenericPlatform/GenericPlatformMemory.h"
#include "GenericPlatform/GenericPlatformDriver.h"
#include "Framework/Application/SlateApplication.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformTypes.h"

#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <Shlwapi.h>

#include "Windows/HideWindowsPlatformTypes.h"
#endif
#include "Kismet/GameplayStatics.h"

UHardwareDataBPLibrary::UHardwareDataBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	
}

bool UHardwareDataBPLibrary::IsWindowsPlatform()
{
	return UGameplayStatics::GetPlatformName() == FString("Windows") ? true : false;
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
	if(IsWindowsPlatform())
	{
		GPUInformation.PrimaryGPUBrand = FWindowsPlatformMisc::GetPrimaryGPUBrand();
		GPUInformation.DeviceDescription = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).DeviceDescription;
		GPUInformation.ProviderName = FWindowsPlatformMisc::GetGPUDriverInfo(FWindowsPlatformMisc::GetPrimaryGPUBrand()).ProviderName;
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
	if(IsWindowsPlatform())
	{
		MemoryInformation.TotalMemoryInGb = FWindowsPlatformMemory::GetPhysicalGBRam();
		MemoryInformation.PhysicalMemoryAvailableInBytes = FWindowsPlatformMemory::GetStats().AvailablePhysical;
		MemoryInformation.VirtualMemoryAvailableInBytes = FWindowsPlatformMemory::GetStats().AvailableVirtual;
		MemoryInformation.PhysicalMemoryUsedInBytes = FWindowsPlatformMemory::GetStats().UsedPhysical;
		MemoryInformation.VirtualMemoryUsedInBytes = FWindowsPlatformMemory::GetStats().UsedVirtual;
	}
	else
	{
		MemoryInformation.TotalMemoryInGb = FGenericPlatformMemory::GetPhysicalGBRam();
		MemoryInformation.PhysicalMemoryAvailableInBytes = FGenericPlatformMemory::GetStats().AvailablePhysical;
		MemoryInformation.VirtualMemoryAvailableInBytes = FGenericPlatformMemory::GetStats().AvailableVirtual;
		MemoryInformation.PhysicalMemoryUsedInBytes = FGenericPlatformMemory::GetStats().UsedPhysical;
		MemoryInformation.VirtualMemoryUsedInBytes = FGenericPlatformMemory::GetStats().UsedVirtual;
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
		OSInformation.IsGamepadConnected = IsGamepadConnected();
		OSInformation.IsMouseConnected = IsMouseConnected();
		OSInformation.IsCapsLockActive = IsCapslockActive();
	}
	else
	{
		OSInformation.ComputerName = FGenericPlatformProcess::ComputerName();
		OSInformation.Username = FGenericPlatformProcess::UserName();
		OSInformation.IsGamepadConnected = IsGamepadConnected();
		OSInformation.IsMouseConnected = IsMouseConnected();
		OSInformation.IsCapsLockActive = IsCapslockActive();
	}
	return OSInformation;
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

FProcessInfo UHardwareDataBPLibrary::GetProcessInformation()
{
	FProcessInfo ProcessInformation;
	if (IsWindowsPlatform())
	{
		ProcessInformation.ProcessId = FWindowsPlatformProcess::GetCurrentProcessId();
		ProcessInformation.ApplicationName = FWindowsPlatformProcess::GetApplicationName(FWindowsPlatformProcess::GetCurrentProcessId());
		ProcessInformation.IsFirstInstance = FWindowsPlatformProcess::IsFirstInstance();
	}
	else
	{
		ProcessInformation.ProcessId = FGenericPlatformProcess::GetCurrentProcessId();
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