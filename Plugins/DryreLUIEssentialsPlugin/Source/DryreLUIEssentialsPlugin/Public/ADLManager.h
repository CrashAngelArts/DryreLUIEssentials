// Copyright © 2024 - DryreL Design

#include <windows.h>
#include <iostream>
#include "ThirdParty/ADL/include/ADLX.h"
#include "ThirdParty/ADL/include/IPerformanceMonitoring.h"
#include "ThirdParty/ADL/ADLXHelper/Windows/Cpp/ADLXHelper.h"

// Function declaration

// Use ADLX namespace
using namespace adlx;

// Initialize ADL
void InitializeADL();

// Function to check if ADLX is initialized
bool IsInitializedADL();

// Initialize ADL
void ShutdownADL();

// Main menu
void MainMenuADL();

// Menu action control
void MenuControlADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Wait for exit with error message
int WaitAndExitADL(const char* msg, const int retCode);

// Show GPU metrics range
void ShowGPUMetricsRangeADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

/*
 * If the app only requires the current metric set, metrics tracking can be omitted in favor of calling the more efficient GetCurrent function.
 * If the app also requires metrics history, GetHistory retrieves the required accumulated history buffer, that may also include the current metric set.
 */
// Show current GPU metrics
void ShowCurrentGPUMetricsADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);
void ShowCurrentGPUMetricsFromHistoricalADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Show historical GPU metrics
void ShowHistoricalGPUMetricsADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU);

// Function to get GPU (given index)
IADLXGPUPtr GetGPUDevice(adlx_uint index);

// Function to get GPU metrics
IADLXGPUMetricsPtr GetGPUMetricsADL(IADLXGPUPtr gpu);

// Function to check GPU usage support status
bool adlIsGPUUsageSupportedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport);

// Function to get GPU usage (in %)
int adlGetGPUUsageADL();

// Get GPU clock speed (in MHz)
int adlGetGPUClockSpeedADL();

// Get GPU VRAM clock speed (in MHz)
int adlGetGPUVRAMClockSpeedADL();

// Display the system time stamp (in ms)
int adlGetTimeStampADL();

// Display GPU temperature(in °C)
int adlGetGPUTemperatureADL();

// Display GPU hotspot temperature(in °C)
int adlGetGPUHotspotTemperatureADL();

// Display GPU power(in W)
int adlGetGPUPowerADL();

// Display GPU total board power(in W)
int adlGetGPUTotalBoardPowerADL();

// Display GPU intake temperature(in °C)
int adlGetGPUIntakeTemperatureADL();

// Display GPU fan speed (in RPM)
int adlGetGPUFanSpeedInRPMADL();

// Display GPU VRAM (in MB)
int adlGetGPUVRAMADL();

// Display GPU Voltage (in mV)
int adlGetGPUVoltageADL();