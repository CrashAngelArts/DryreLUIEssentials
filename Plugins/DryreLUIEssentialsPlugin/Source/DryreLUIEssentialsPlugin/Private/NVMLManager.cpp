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
	nvmlReturn_t result = nvmlInit();
	return result == NVML_SUCCESS;
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

// Function to get GPU device by index
nvmlDevice_t GetGPUDevice(int index)
{
	nvmlReturn_t result;
	nvmlDevice_t device;

	// Get the device handle (here, index represents the GPU index)
	result = nvmlDeviceGetHandleByIndex(index, &device);
	if (result != NVML_SUCCESS) {
		// Print or log an error message
		printf("Error getting device handle: %s\n", nvmlErrorString(result));
		return nullptr; // Return nullptr on error
	}

	return device;
}

int nvGPUUtilizationNVML(int Index)
{
	if(nvIsInitializedNVML())
	{
		nvmlReturn_t result;

		// Get GPU device
		nvmlDevice_t device = GetGPUDevice(Index);
		if (!device) {
			// Handle device retrieval error
			printf("Error getting GPU device.\n");
			return -1;
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

int nvMemoryUtilizationNVML(int Index)
{
	if(nvIsInitializedNVML())
	{
		nvmlReturn_t result;
		
		// Get GPU device
		nvmlDevice_t device = GetGPUDevice(Index);
		if (!device) {
			// Handle device retrieval error
			printf("Error getting GPU device.\n");
			return -1;
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

int nvGetGPUClockSpeedNVML(int Index)
{
	if(nvIsInitializedNVML())
	{
		nvmlReturn_t result;
	
		// Get GPU device
		nvmlDevice_t device = GetGPUDevice(Index);
		if (!device) {
			// Handle device retrieval error
			printf("Error getting GPU device.\n");
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
int nvGetGPUVRAMClockSpeedNVML(int Index)
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
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
int nvGetGPUTemperatureNVML(int Index)
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
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

// Display GPU temperature threshold (in °C)
int nvGetGPUTemperatureThresholdNVML(int Index)
{
	if (!nvIsInitializedNVML()) {
		// Handle NVML not initialized
		return -1;
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int temperatureThreshold;
	result = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_GPU_MAX, &temperatureThreshold);
	if (result != NVML_SUCCESS) {
		// Handle temperature threshold retrieval error
		printf("Error on temperature threshold retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

	// Shutdown NVML before returning
	nvGPUShutdownNVML();

	// Return the GPU temperature threshold as an integer
	return static_cast<int>(temperatureThreshold);
}

// Display GPU power (in W)
int nvGetGPUPowerNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML()) {
		// Handle initialization error
		printf("NVML is not initialized.\n");
		return -1;
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int power;
	result = nvmlDeviceGetPowerUsage(device, &power);
	if (result != NVML_SUCCESS) {
		// Handle power retrieval error
		printf("Error on power retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

	// Return GPU power as an integer
	return static_cast<int>(power);
}

// Display GPU fan speed (in &)
int nvGetGPUFanSpeedNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML()) {
		// Handle initialization error
		printf("NVML is not initialized.\n");
		return -1;
	}

	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int fanSpeed;
	nvmlReturn_t result = nvmlDeviceGetFanSpeed(device, &fanSpeed);
	if (result != NVML_SUCCESS) {
		// Handle fan speed retrieval error
		printf("Error on fan speed retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

	// Return GPU fan speed as an integer
	return static_cast<int>(fanSpeed);
}

// Display GPU VRAM (in MB)
int nvGetGPUVRAMNVML(int Index, FString state)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML()) {
		// Handle initialization error
		printf("NVML is not initialized.\n");
		return -1;
	}

	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	nvmlMemory_t memoryInfo;
	nvmlReturn_t result = nvmlDeviceGetMemoryInfo(device, &memoryInfo);
	if (result != NVML_SUCCESS) {
		// Handle memory info retrieval error
		printf("Error on memory info retrieval: %s\n", nvmlErrorString(result));
		return -1;
	}

    int byteToMB = (1024 * 1024);
	
	// Return used GPU memory size as an integer (convert bytes to megabytes)
	if(state == "used" || state == "USED")
	{
		return static_cast<int>(memoryInfo.used / byteToMB);
	}
	else if (state == "free" || state == "FREE")
	{
		return static_cast<int>(memoryInfo.free / byteToMB);
	}
	else if (state == "total" || state == "TOTAL")
	{
		return static_cast<int>(memoryInfo.total / byteToMB);
	}
	else return -1;
}

// Display GPU Voltage (in mV)
int nvGetGPUVoltageNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML()) {
		// Handle initialization error
		printf("NVML is not initialized.\n");
		return -1;
	}

	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	int gpuPower = nvGetGPUPowerNVML(Index);
	int volts = 12;
	int voltage = gpuPower / volts;

	// Return GPU voltage as an integer
	return static_cast<int>(voltage);
}

// Number of Fans
int nvGetNumFansNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return -1;  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int numFans;
	result = nvmlDeviceGetNumFans (device, &numFans);
	if (result != NVML_SUCCESS)
	{
		// Handle fan speed info retrieval error
		printf("Error on fan speed info retrieval: %s\n", nvmlErrorString(result));
		return -1;  // or another appropriate value
	}

	return numFans;
}

// Number of GPU Cores
int nvGetNumGpuCoresNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return -1;  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int numGpuCores;
	result = nvmlDeviceGetNumGpuCores(device, &numGpuCores);
	if (result != NVML_SUCCESS)
	{
		// Handle GPU cores info retrieval error
		printf("Error on GPU cores info retrieval: %s\n", nvmlErrorString(result));
		return -1;  // or another appropriate value
	}
	return numGpuCores;
}

// Get Architecture
int nvGetArchitectureNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return -1;  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	nvmlDeviceArchitecture_t arch;
	result = nvmlDeviceGetArchitecture(device, &arch);
	if (result != NVML_SUCCESS)
	{
		// Handle architecture retrieval error
		printf("Error on architecture retrieval: %s\n", nvmlErrorString(result));
		return -1;  // or another appropriate value
	}

	return static_cast<int>(arch);
}

// BAR1 Memory Info
int nvGetBAR1MemoryInfoNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return -1;  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	nvmlBAR1Memory_t bar1MemoryInfo;
	result = nvmlDeviceGetBAR1MemoryInfo(device, &bar1MemoryInfo);
	if (result != NVML_SUCCESS)
	{
		// Handle BAR1 memory info retrieval error
		printf("Error on BAR1 memory info retrieval: %s\n", nvmlErrorString(result));
		return -1;  // or another appropriate value
	}

	int byteToMB = 1024 * 1024;
	
	// Return the BAR1 memory size in megabytes
	return static_cast<int>(bar1MemoryInfo.bar1Total / byteToMB);
}

// BAR1 Board ID
int nvGetBoardIDNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return -1;  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return -1;
	}

	unsigned int boardId;
	result = nvmlDeviceGetBoardId(device, &boardId);
	if (result != NVML_SUCCESS)
	{
		// Handle board ID retrieval error
		printf("Error on board ID retrieval: %s\n", nvmlErrorString(result));
		return -1;  // or another appropriate value
	}

	// Return the board ID
	return static_cast<int>(boardId);
}

// Board Part Number
FString nvGetBoardPartNumberNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		return "NVML is not initialized";  // or another appropriate value
	}

	nvmlReturn_t result;
	
	// Get GPU device
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device) {
		// Handle device retrieval error
		printf("Error getting GPU device.\n");
		return "Error getting GPU device.";
	}

	char boardPartNumber[NVML_DEVICE_PART_NUMBER_BUFFER_SIZE];
	result = nvmlDeviceGetBoardPartNumber(device, boardPartNumber, NVML_DEVICE_PART_NUMBER_BUFFER_SIZE);
	if (result != NVML_SUCCESS)
	{
		// Handle board part number retrieval error
		FString ErrorMessage = FString::Printf(TEXT("Error on board part number retrieval: %s"), ANSI_TO_TCHAR(nvmlErrorString(result)));
		nvmlShutdown();
		return ErrorMessage;
	}

	// Convert char array to FString
	FString BoardPartNumberStr = FString(ANSI_TO_TCHAR(boardPartNumber));

	// Print or use the board part number as needed
	UE_LOG(LogTemp, Warning, TEXT("The board part number is: %s"), *BoardPartNumberStr);

	// Return the board part number as FString
	nvmlShutdown();
	return BoardPartNumberStr;
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
