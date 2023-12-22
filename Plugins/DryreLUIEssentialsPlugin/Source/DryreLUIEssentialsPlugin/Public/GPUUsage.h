#include <iostream>
#include "ThirdParty/NVML/include/nvml.h"

// Function declaration
int nvGPUInitializeNVML();
int nvGPUShutdownNVML();
int nvGPUUtilizationNVML();
int nvGPUTemperatureNVML();
int nvGPUDeviceCountNVML();