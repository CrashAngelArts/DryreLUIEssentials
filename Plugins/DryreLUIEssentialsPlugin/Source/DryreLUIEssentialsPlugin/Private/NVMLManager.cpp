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

// Get GPU VRAM clock speed (in MHz)
int nvGetGPUVRAMClockSpeedNVML()
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlDevice_t device;
	nvmlReturn_t result = nvmlDeviceGetHandleByIndex(0, &device); // Assuming you want to get information for the first GPU
	if (result != NVML_SUCCESS) {
		// Handle error getting device handle
		printf("Error on getting NVML device handle: %s\n", nvmlErrorString(result));
		nvGPUShutdownNVML();
		return -1;
	}

	unsigned int vramClock;
	result = nvmlDeviceGetClockInfo(device, NVML_CLOCK_MEM, &vramClock);
	if (result != NVML_SUCCESS) {
		// Handle error getting VRAM clock info
		printf("Error on getting GPU VRAM clock speed: %s\n", nvmlErrorString(result));
		nvGPUShutdownNVML();
		return -1;
	}

	// Shutdown NVML before returning
	nvGPUShutdownNVML();

	// Return GPU VRAM clock speed as an integer
	return static_cast<int>(vramClock);
}

// Display GPU temperature(in °C)
int nvGetGPUTemperatureNVML(int gpuIndex)
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlDevice_t device;
	nvmlReturn_t result = nvmlDeviceGetHandleByIndex(gpuIndex, &device);
	if (result != NVML_SUCCESS) {
		// Handle device retrieval error
		printf("Error on device retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

	unsigned int temperature;
	result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature);
	if (result != NVML_SUCCESS) {
		// Handle temperature retrieval error
		printf("Error on temperature retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

	// Shutdown NVML before returning
	nvGPUShutdownNVML();

	// Return the GPU temperature as an integer
	return static_cast<int>(temperature);
}

/*
// Display the system time stamp (in ms)
int nvGetTimeStampNVML()
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlDevice_t device;
	nvmlReturn_t result = nvmlDeviceGetHandleByIndex(0, &device); // Assuming you want to get information for the first GPU
	if (result != NVML_SUCCESS) {
		// Handle error getting device handle
		printf("Error on getting NVML device handle: %s\n", nvmlErrorString(result));
		nvGPUShutdownNVML();
		return -1;
	}

	nvmlValueType_t valueType;
	unsigned long long timeStamp;
	result = nvmlDeviceGetTimeStamp(device, &timeStamp);
	if (result != NVML_SUCCESS) {
		// Handle error getting GPU timestamp
		printf("Error on getting GPU timestamp: %s\n", nvmlErrorString(result));
		nvGPUShutdownNVML();
		return -1;
	}

	// Shutdown NVML before returning
	nvGPUShutdownNVML();

	// Return GPU timestamp as an integer
	return static_cast<int>(timeStamp);
}
*/
