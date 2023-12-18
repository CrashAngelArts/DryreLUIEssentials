// Copyright © 2024 - DryreL Design

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformDriver.h"
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
	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int32 TotalMemoryInGb;
	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int64 PhysicalMemoryAvailableInBytes;
	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int64 VirtualMemoryAvailableInBytes;
	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int64 PhysicalMemoryUsedInBytes;
	UPROPERTY(BlueprintReadOnly, Category = "Memory Info")
	int64 VirtualMemoryUsedInBytes;
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