#include <windows.h>
#include <iostream>
#include "ThirdParty/ADL/include/ADLX.h"
#include "ThirdParty/ADL/include/ADLXDefines.h"
#include "ThirdParty/ADL/include/ADLXStructures.h"
#include "ThirdParty/ADL/include/IPerformanceMonitoring.h"
#include "ThirdParty/ADL/include/ISystem.h"
#include "ThirdParty/ADL/ADLXHelper/Windows/Cpp/ADLXHelper.h"

// Function declaration

// Use ADLX namespace
using namespace adlx;

// Initialize ADL
void InitializeADL();

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
IADLXGPUPtr GetGPUAtIndex(adlx_uint index);

// Function to get GPU metrics
IADLXGPUMetricsPtr GetGPUMetricsADL(IADLXGPUPtr gpu);

// Function to check GPU usage support status
bool adlIsGPUUsageSupportedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport);

// Function to get GPU usage (in %)
int adlGetGPUUsageADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics);