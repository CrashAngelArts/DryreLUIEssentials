// Copyright © 2024 - DryreL Design

#include "NVMLManager.h"

int main() {
	
}

int nvGPUInitializeNVML()
{
	nvmlReturn_t result;

	// Initialize NVML
	result = nvmlInit();
	if (result != NVML_SUCCESS) {
		// Handle initialization error
		printf("Error on nvml initialization: %s\n", nvmlErrorString(result));
		return -1;
	}
	return 0;
}

int nvGPUShutdownNVML()
{
	nvmlReturn_t result;

	// Shutdown NVML
	result = nvmlShutdown();
	if (result != NVML_SUCCESS) {
		// Handle shutdown error
		printf("Error on nvml Shutdown: %s\n", nvmlErrorString(result));
		return -2;
	}
	return 0;
}

int nvGPUUtilizationNVML()
{
	nvmlReturn_t result;
	nvmlDevice_t device;

	// Get the device handle (here, index 0 represents the first GPU)
	result = nvmlDeviceGetHandleByIndex(0, &device);
	if (result != NVML_SUCCESS) {
		// Print or log an error message
		printf("Error getting device handle: %s\n", nvmlErrorString(result));
		nvmlShutdown();
		return -3;
	}

	// 'utilization' now contains the GPU utilization percentage
	nvmlUtilization_t utilization;
	result = nvmlDeviceGetUtilizationRates(device, &utilization);
	if (result != NVML_SUCCESS) {
		// Print or log an error message
		printf("Error getting GPU utilization rates: %s\n", nvmlErrorString(result));
		nvmlShutdown();
		return -4;
	}

	// Access individual utilization values
	int customgpuUtilization = utilization.gpu;
	int custommemoryUtilization = utilization.memory;
	
	return customgpuUtilization;
}

int nvGPUTemperatureNVML()
{
	nvmlReturn_t result;
	nvmlDevice_t device;
	nvGPUInitializeNVML();
	
	int deviceCount = nvGPUDeviceCountNVML();

	result = nvmlDeviceGetHandleByIndex(0, &device);
	if (result != NVML_SUCCESS) {
		std::cerr << "Failed to get device handle: " << nvmlErrorString(result) << std::endl;
		nvmlShutdown();
		return -5;
	}
	
	// Get the GPU temperature
	unsigned int temperature;
	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature);
	if (result != NVML_SUCCESS) {
		printf("Failed to get GPU temperature: %s\n", nvmlErrorString(result));
		nvmlShutdown();
		return -6;
	}

	return temperature;
}

int nvGPUDeviceCountNVML()
{
	nvmlReturn_t result;

	unsigned int deviceCount;
	result = nvmlDeviceGetCount(&deviceCount);
	if (result != NVML_SUCCESS || deviceCount == 0) {
		printf("No NVIDIA GPU found or failed to get device count");

		nvmlShutdown();
		return -7;
	}
	return deviceCount;
}