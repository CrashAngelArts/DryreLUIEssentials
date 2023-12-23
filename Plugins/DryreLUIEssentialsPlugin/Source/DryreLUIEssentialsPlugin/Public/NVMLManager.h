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