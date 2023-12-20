// Copyright © 2024 - DryreL Design

#pragma once

#include "CoreMinimal.h"
#include "Windows/WindowsHWrapper.h"
#include "GenericPlatform/GenericPlatformDriver.h"

#include <stdlib.h>
#include <stddef.h>
#include "HAL/Platform.h"

#include "GeneralStructures.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FCPUInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		FString CPUBrand;
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		FString CPUChipset;
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		FString CPUVendor;
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		int32 CPUCores;
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		int32 CPUCoresWithHyperthread;
	UPROPERTY(BlueprintReadOnly, Category = "CPU Info")
		float CPUUsage;
};

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FGPUInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString PrimaryGPUBrand;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString DeviceDescription;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString ProviderName;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		int32 AvailableVRAM;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		int32 CurrentVRAM;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		int32 TotalVRAM;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		int32 ReservedCurrentVRAM;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		int32 ReservedAvailableVRAM;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString InternalDriverVersion;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString UserDriverVersion;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString DriverDate;
	UPROPERTY(BlueprintReadOnly, Category = "GPU Info")
		FString RHIName;
};

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FMemInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Memory RAM Info")
	int32 TotalMemoryInGB;
	UPROPERTY(BlueprintReadOnly, Category = "Memory RAM Info")
	int32 PhysicalMemoryAvailableInMB;
	UPROPERTY(BlueprintReadOnly, Category = "Memory RAM Info")
	int32 VirtualMemoryAvailableInMB;
	UPROPERTY(BlueprintReadOnly, Category = "Memory RAM Info")
	int32 PhysicalMemoryUsedInMB;
	UPROPERTY(BlueprintReadOnly, Category = "Memory RAM Info")
	int32 VirtualMemoryUsedInMB;
};

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FOSInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	FString ComputerName;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	FString Username;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	int LaptopBatteryLevel;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool Is64Bit;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool IsDesktopTouchScreen;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool IsHDRUsedByDefault;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool IsGamepadConnected;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool IsMouseConnected;
	UPROPERTY(BlueprintReadOnly, Category = "OS Info")
	bool IsCapsLockActive;
};

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FProcessInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Process Info")
	int32 ProcessId;
	UPROPERTY(BlueprintReadOnly, Category = "Process Info")
	FString ApplicationName;
	UPROPERTY(BlueprintReadOnly, Category = "Process Info")
	bool IsFirstInstance;
};

USTRUCT(BlueprintType)
struct DRYRELUIESSENTIALSPLUGIN_API FDeviceInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Device Info")
	float DeviceTemperature;
	UPROPERTY(BlueprintReadOnly, Category = "Device Info")
	float DeviceVolume;
};