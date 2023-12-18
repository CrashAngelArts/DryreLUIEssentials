// Copyright © 2024 - DryreL Design

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GeneralStructures.h"
#include "HardwareDataBPLibrary.generated.h"

UCLASS()
class UHardwareDataBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	
	UFUNCTION()
	static bool IsWindowsPlatform();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FCPUInfo GetCPUInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static float GetCPUUsage();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FGPUInfo GetGPUInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FMemInfo GetMemoryInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FOSInfo GetOSInfo();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static bool IsGamepadConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static bool IsMouseConnected();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static bool IsCapslockActive();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FProcessInfo GetProcessInformation();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "DryreL Design")
	static FDeviceInfo GetDeviceInformation();
	
};
