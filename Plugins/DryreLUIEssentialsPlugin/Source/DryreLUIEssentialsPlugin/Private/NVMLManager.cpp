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

int nvGPUUsageNVML(int Index)
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
int nvGetGPUVRAMNVML(int Index, E_NV_VRAM_STATUS_NVML state)
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

	const double byteToMB = (1024 * 1024);
	
	switch (state) {
	case E_NV_VRAM_STATUS_NVML::Free:
		return static_cast<int>(memoryInfo.free / byteToMB);
		break;
	case E_NV_VRAM_STATUS_NVML::Used:
		return static_cast<int>(memoryInfo.used / byteToMB);
		break;
	case E_NV_VRAM_STATUS_NVML::Total:
		return static_cast<int>(memoryInfo.total / byteToMB);
		break;
	default:
		std::cerr << "Invalid state!" << std::endl;
		return static_cast<int>(memoryInfo.free / byteToMB);
	}
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

// GPU Brand Type
int nvGetGPUBrandTypeNVML(int Index)
{
	if (!nvIsInitializedNVML())
	{
		// Handle the case where NVML is not initialized
		UE_LOG(LogTemp, Warning, TEXT("NVML Not Initialized"));
		return -1;  // or another appropriate value
	}

	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Warning, TEXT("Error getting GPU device."));
		return -1;  // or another appropriate value
	}

	nvmlBrandType_t brandType;
	nvmlReturn_t result = nvmlDeviceGetBrand(device, &brandType);
	if (result != NVML_SUCCESS)
	{
		// Handle brand retrieval error
		UE_LOG(LogTemp, Warning, TEXT("Error on brand retrieval: %s"), ANSI_TO_TCHAR(nvmlErrorString(result)));
		nvmlShutdown();
		return -1;  // or another appropriate value
	}

	// Return the brand type as an integer
	nvmlShutdown();
	return static_cast<int>(brandType);
}

FString nvGetGPUBrandNVML(int Index)
{
	int brandType = nvGetGPUBrandTypeNVML(Index);
	switch (brandType)
	{
	case 0:
		return "UNKNOWN";
	case 1:
		return "QUADRO";
	case 2:
		return "TESLA";
	case 3:
		return "NVS";
	case 4:
		return "GRID";
	case 5:
		return "GEFORCE";
	case 6:
		return "TITAN";
	case 7:
		return "NVIDIA VAPPS";
	case 8:
		return "NVIDIA VPC";
	case 9:
		return "NVIDIA VCS";
	case 10:
		return "NVIDIA VWS";
	case 11:
		return "NVIDIA Cloud Gaming";
	case 12:
		return "NVIDIA VGAMING";
	case 13:
		return "QUADRO RTX";
	case 14:
		return "NVIDIA RTX";
	case 15:
		return "NVIDIA";
	case 16:
		return "GEFORCE RTX";
	case 17:
		return "TITAN RTX";
	case 18:
		return "BRAND COUNT: " + IntToFString(brandType);
	default:
		return "INVALID BRAND TYPE";
	}

}

// Function to convert int to FString
FString IntToFString(int Number)
{
	// Using FString::Printf to format the int as a string
	return FString::Printf(TEXT("%d"), Number);
}

// Function to get the count of GPU devices
int nvGetGPUGetCountNVML()
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		printf("Error initializing NVML.\n");
		return -1;
	}

	unsigned int deviceCount;
	nvmlReturn_t result = nvmlDeviceGetCount_v2(&deviceCount);

	// Check for errors in getting GPU count
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting GPU count
		printf("Error getting GPU count: %s\n", nvmlErrorString(result));
		return -1;
	}

	// Return the count of GPU devices as an integer
	return static_cast<int>(deviceCount);
}

int nvGetGPUGetMemoryBusWidthNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return -1;
	}

	nvmlReturn_t result;
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return -1;  // or another appropriate value
	}

	unsigned int busWidth;
	result = nvmlDeviceGetMemoryBusWidth(device, &busWidth);

	// Check for errors in getting memory bus width
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting memory bus width
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device: %s"));
		return -1;
	}

	// Return the memory bus width as an integer
	return static_cast<int>(busWidth);
}

// Function to get the name of the GPU device
FString nvGetGPUGetNameNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return FString(TEXT("-1"));
	}

	nvmlReturn_t result;
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return "-1";  // or another appropriate value
	}

	// Assuming a reasonable maximum length for the GPU name
	const int MaxNameLength = 64;
	char name[MaxNameLength];

	result = nvmlDeviceGetName(device, name, MaxNameLength);

	// Check for errors in getting GPU name
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting GPU name
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU name: %s"), *FString(nvmlErrorString(result)));
		return FString(TEXT("-1"));
	}

	// Return the GPU name as FString
	return FString(UTF8_TO_TCHAR(name));
}

// Function to get the PCIe speed of the GPU device
int nvGetGPUGetPcieSpeedNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return -1;
	}

	nvmlDevice_t device = GetGPUDevice(Index);
	nvmlReturn_t result;
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return -1;  // or another appropriate value
	}

	unsigned int pcieSpeed;
	result = nvmlDeviceGetPcieSpeed(device, &pcieSpeed);

	// Check for errors in getting PCIe speed
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting PCIe speed
		UE_LOG(LogTemp, Error, TEXT("Error getting PCIe speed: %s"), *FString(nvmlErrorString(result)));
		return -1;
	}

	// Return the PCIe speed
	return static_cast<int>(pcieSpeed);
}

// Function to get the VBIOS version of the GPU device
FString nvGetGPUGetVBIOSVersionNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return "-1";
	}

	nvmlReturn_t result;
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return "-1";  // or another appropriate value
	}

	const int maxLength = 256;
	char version[maxLength];
	result = nvmlDeviceGetVbiosVersion(device, version, maxLength);

	// Check for errors in getting VBIOS version
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting VBIOS version
		UE_LOG(LogTemp, Error, TEXT("Error getting VBIOS version: %s"), *FString(nvmlErrorString(result)));
		return "-1";
	}

	// Return the VBIOS version as FString
	return FString(version);
}

// Function to get the CUDA compute capability of the GPU device
int nvGetGPUGetCudaComputeCapabilityNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		// Handle NVML initialization error
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return -1;
	}

	nvmlReturn_t result;
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return -1;  // or another appropriate value
	}

	int major, minor;
	result = nvmlDeviceGetCudaComputeCapability(device, &major, &minor);

	// Check for errors in getting CUDA compute capability
	if (result != NVML_SUCCESS)
	{
		// Handle error in getting CUDA compute capability
		UE_LOG(LogTemp, Error, TEXT("Error getting CUDA compute capability: %s"), *FString(nvmlErrorString(result)));
		return -1;
	}

	// Return the CUDA compute capability as an integer
	return major * 10 + minor;
}

bool nvGetGPUCudaAvailabilityNVML(int Index)
{
	if(nvIsInitializedNVML())
	{
		return (GetGPUDevice(Index)) ? true : false;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error initializing NVML."));
		return false;
	}
	return false;
}

// Function to get GPU power state as FString
FString nvGetGPUGetPowerStateNVML(int Index)
{
	// Check if NVML is initialized
	if (!nvIsInitializedNVML())
	{
		UE_LOG(LogTemp, Error, TEXT("NVML is not initialized."));
		return FString(TEXT("NVML not initialized"));
	}

	nvmlReturn_t result;
	nvmlDevice_t device = GetGPUDevice(Index);
	if (!device)
	{
		// Handle device retrieval error
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU device"));
		return "-1";  // or another appropriate value
	}

	// Get GPU power state
	nvmlPstates_t powerState;
	result = nvmlDeviceGetPowerState(device, &powerState);

	if (result != NVML_SUCCESS)
	{
		UE_LOG(LogTemp, Error, TEXT("Error getting GPU power state: %s"), ANSI_TO_TCHAR(nvmlErrorString(result)));
		return FString(TEXT("Error getting GPU power state"));
	}

	// Finalize NVML
	nvmlShutdown();

	// Convert power state enum to FString
	FString powerStateString;
	switch (powerState)
	{
	case NVML_PSTATE_0:
		powerStateString = FString(TEXT("Maximum Performance"));
		break;
	case NVML_PSTATE_1:
		powerStateString = FString(TEXT("Performance state 1"));
		break;
	case NVML_PSTATE_2:
		powerStateString = FString(TEXT("Performance state 2"));
		break;
	case NVML_PSTATE_3:
		powerStateString = FString(TEXT("Performance state 3"));
		break;
	case NVML_PSTATE_4:
		powerStateString = FString(TEXT("Performance state 4"));
		break;
	case NVML_PSTATE_5:
		powerStateString = FString(TEXT("Performance state 5"));
		break;
	case NVML_PSTATE_6:
		powerStateString = FString(TEXT("Performance state 6"));
		break;
	case NVML_PSTATE_7:
		powerStateString = FString(TEXT("Performance state 7"));
		break;
	case NVML_PSTATE_8:
		powerStateString = FString(TEXT("Performance state 8"));
		break;
	case NVML_PSTATE_9:
		powerStateString = FString(TEXT("Performance state 9"));
		break;
	case NVML_PSTATE_10:
		powerStateString = FString(TEXT("Performance state 10"));
		break;
	case NVML_PSTATE_11:
		powerStateString = FString(TEXT("Performance state 11"));
		break;
	case NVML_PSTATE_12:
		powerStateString = FString(TEXT("Performance state 12"));
		break;
	case NVML_PSTATE_13:
		powerStateString = FString(TEXT("Performance state 13"));
		break;
	case NVML_PSTATE_14:
		powerStateString = FString(TEXT("Performance state 14"));
		break;
	case NVML_PSTATE_15:
		powerStateString = FString(TEXT("Minimum Performance"));
		break;
	case NVML_PSTATE_UNKNOWN:
		powerStateString = FString(TEXT("Unknown power state"));
		break;
	default:
		powerStateString = FString(TEXT("Invalid power state"));
		break;
	}

	return powerStateString;
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
