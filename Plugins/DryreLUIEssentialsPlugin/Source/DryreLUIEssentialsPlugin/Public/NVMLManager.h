// Copyright © 2024 - DryreL Design

#include <iostream>
#include "ThirdParty/NVML/include/nvml.h"

// Function declaration

// Initialize NVML
int nvGPUInitializeNVML();

// Is Initialized?
bool nvIsInitializedNVML();

// Shutdown NVML
int nvGPUShutdownNVML();

// Function to get GPU device by index
nvmlDevice_t GetGPUDevice(int Index);

// Function to get GPU usage (in %)
int nvGPUUtilizationNVML(int Index);

// Function to get GPU Memory usage (in %)
int nvMemoryUtilizationNVML(int Index);

// Function to get GPU Device Count
int nvGPUDeviceCountNVML();

// Get GPU clock speed (in MHz)
int nvGetGPUClockSpeedNVML(int Index);

// Get GPU VRAM clock speed (in MHz)
int nvGetGPUVRAMClockSpeedNVML(int Index);

/*
// Display the system time stamp (in ms)
int nvGetTimeStampNVML();
*/

// Display GPU temperature (in °C)
int nvGetGPUTemperatureNVML(int Index);

// Display GPU temperature threshold (in °C)
int nvGetGPUTemperatureThresholdNVML(int Index);

// Display GPU power (in W)
int nvGetGPUPowerNVML(int Index);

// Display GPU fan speed (in &)
int nvGetGPUFanSpeedNVML(int Index);

// Display GPU VRAM Used (in MB)
int nvGetGPUVRAMNVML(int Index, FString state);

// Display GPU Voltage (in mV)
int nvGetGPUVoltageNVML(int Index);

// Number of Fans
int nvGetNumFansNVML(int Index);

// Number of GPU Cores
int nvGetNumGpuCoresNVML(int Index);

// Number of GPU Cores
int nvGetNumGpuCoresNVML(int Index);

// Architecture
int nvGetArchitectureNVML(int Index);

// BAR1 Memory Info
int nvGetBAR1MemoryInfoNVML(int Index);

// BAR1 Board ID
int nvGetBoardIDNVML(int Index);

// Board Part Number
FString nvGetBoardPartNumberNVML(int Index);

// GPU Brand Type
int nvGetGPUBrandTypeNVML(int Index);

// GPU Brand
FString nvGetGPUBrandNVML(int Index);

// Function to convert int to FString
FString IntToFString(int Number);

