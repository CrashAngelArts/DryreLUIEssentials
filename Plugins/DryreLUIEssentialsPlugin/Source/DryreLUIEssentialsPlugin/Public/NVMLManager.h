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
int nvGPUUtilizationNVML();

// Function to get GPU Memory usage (in %)
int nvMemoryUtilizationNVML();

// Function to get GPU temperature (in Celsius)
int nvGPUTemperatureNVML();

// Function to get GPU Device Count
int nvGPUDeviceCountNVML();