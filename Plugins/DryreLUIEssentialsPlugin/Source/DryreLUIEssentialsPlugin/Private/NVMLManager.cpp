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

// Is Initialized?
bool nvIsInitializedNVML()
{
	nvmlReturn_t result;

	// Initialize NVML
	result = nvmlInit();
	if (result == NVML_SUCCESS) {
		// NVML initialization successful
		return true;
	} else {
		// Handle initialization error
		printf("Error on NVML initialization: %s\n", nvmlErrorString(result));
		return false;
	}
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
	if(nvIsInitializedNVML())
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
	
		return customgpuUtilization;
	}
	return 0;
}

int nvMemoryUtilizationNVML()
{
	if(nvIsInitializedNVML())
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
		int custommemoryUtilization = utilization.memory;
	
		return custommemoryUtilization;
	}
	return 0;
}

int nvGPUTemperatureNVML()
{
	if(nvIsInitializedNVML())
	{
		nvmlReturn_t result;
		nvmlDevice_t device;
	
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
	return 0;
}

int nvGPUDeviceCountNVML()
{
	if(nvIsInitializedNVML())
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
	return 0;
}

int nvGetGPUClockSpeedNVML()
{
	if(nvIsInitializedNVML())
	{
		nvmlReturn_t result;
	
		nvmlDevice_t device;
		result = nvmlDeviceGetHandleByIndex(0, &device); // Assuming you want to get information for the first GPU
		if (result != NVML_SUCCESS) {
			// Handle error getting device handle
			printf("Error on getting NVML device handle: %s\n", nvmlErrorString(result));
			nvmlShutdown();
			return -1;
		}

		unsigned int clock;
		result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_SM, &clock);
		if (result != NVML_SUCCESS) {
			// Handle error getting clock info
			printf("Error on getting GPU clock speed: %s\n", nvmlErrorString(result));
			nvmlShutdown();
			return -1;
		}
		// Return GPU clock speed as an integer
		return static_cast<int>(clock);
	}
	return 0;
}
