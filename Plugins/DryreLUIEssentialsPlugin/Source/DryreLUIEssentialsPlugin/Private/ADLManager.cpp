//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainPerfGPUMetrics.cpp
/// \brief Demonstrates how to control GPU metrics when programming with ADLX.

#include "ADLManager.h"

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;

// ASCII °
static const int g_degree = 248;

/*
int main()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();

    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringService;
        res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringService);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPUListPtr gpus;
            // Get GPU list
            res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
            if (ADLX_SUCCEEDED(res))
            {
                // Use the first GPU in the list
                IADLXGPUPtr oneGPU;
                res = gpus->At(gpus->Begin(), &oneGPU);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenuADL();
                    // Get and execute the choice
                    MenuControlADL(perfMonitoringService, oneGPU);
                }
                else
                    std::cout << "\tGet particular GPU failed" << std::endl;
            }
            else
                std::cout << "\tGet GPU list failed" << std::endl;
        }
        else
            std::cout << "\tGet performance monitoring services failed" << std::endl;
    }
    else
        return WaitAndExitADL("\tg_ADLXHelp initialize failed", 0);

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}
*/

void adlInitializeADL()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    
    if (ADLX_SUCCEEDED(res))
    {
        // Get Performance Monitoring services
        IADLXPerformanceMonitoringServicesPtr perfMonitoringService;
        res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringService);
        if (ADLX_SUCCEEDED(res))
        {
            IADLXGPUListPtr gpus;
            // Get GPU list
            res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);
            if (ADLX_SUCCEEDED(res))
            {
                // Use the first GPU in the list
                IADLXGPUPtr oneGPU;
                res = gpus->At(gpus->Begin(), &oneGPU);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display main menu options
                    MainMenuADL();
                    // Get and execute the choice
                    MenuControlADL(perfMonitoringService, oneGPU);
                }
                else
                    std::cout << "\tGet particular GPU failed" << std::endl;
            }
            else
                std::cout << "\tGet GPU list failed" << std::endl;
        }
        else
            std::cout << "\tGet performance monitoring services failed" << std::endl;
    }
}

bool adlIsInitializedADL()
{
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    
    if (ADLX_SUCCEEDED(res))
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

void adlShutdownADL()
{
    ADLX_RESULT res = ADLX_FAIL;
    
    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX result: " << res << std::endl;
}

// Main menu
void MainMenuADL()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display GPU metrics range" << std::endl;
    std::cout << "\t->Press 2 to display current GPU metrics" << std::endl;
    std::cout << "\t->Press 3 to display current GPU metrics from historical data" << std::endl;
    std::cout << "\t->Press 4 to display historical GPU metrics" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display the main menu options" << std::endl;
}

// Menu action control
void MenuControlADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
        // Show GPU metrics range
        case '1':
            ShowGPUMetricsRangeADL(perfMonitoringServices, oneGPU);
            break;

        // Display current GPU metrics
        case '2':
            ShowCurrentGPUMetricsADL(perfMonitoringServices, oneGPU);
            break;

        // Display current GPU metrics from historical data
        case '3':
            ShowCurrentGPUMetricsFromHistoricalADL(perfMonitoringServices, oneGPU);
            break;

        // Display historical GPU metrics
        case '4':
            ShowHistoricalGPUMetricsADL(perfMonitoringServices, oneGPU);
            break;

        // 	Display menu options
        case 'm':
        case 'M':
            MainMenuADL();
            break;
        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExitADL(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}

// Display GPU metrics range
void ShowGPUMetricsRangeADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    ADLX_RESULT res = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);
    if (ADLX_SUCCEEDED(res))
    {
        adlx_int minValue = 0, maxValue = 0;

        // Get GPU usage range
        res = gpuMetricsSupport->GetGPUUsageRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU usage range between " << minValue << "% and " << maxValue << "%" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU usage range" << std::endl;

        // Get GPU clock speed range
        res = gpuMetricsSupport->GetGPUClockSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU clock speed range between " << minValue << "MHz and " << maxValue << "MHz" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU clock speed range" << std::endl;

        // Get GPU VRAM clock speed range
        res = gpuMetricsSupport->GetGPUVRAMClockSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU VRAM clock speed range between " << minValue << "MHz and " << maxValue << "MHz" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU VRAM clock speed range" << std::endl;

        // Get GPU temperature range
        res = gpuMetricsSupport->GetGPUTemperatureRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU temperature range between " << minValue << g_degree << "C and " << maxValue << g_degree << "C" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU temperature range" << std::endl;

        // Get GPU hotspot temperature range
        res = gpuMetricsSupport->GetGPUHotspotTemperatureRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU hotspot temperature range between " << minValue << g_degree << "C and " << maxValue << g_degree << "C" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU hotspot temperature range" << std::endl;

        // Get GPU power range
        res = gpuMetricsSupport->GetGPUPowerRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU power range between " << minValue << "W and " << maxValue << "W" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU power range" << std::endl;

        // Get GPU fan speed range
        res = gpuMetricsSupport->GetGPUFanSpeedRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU fan speed range between " << minValue << "RPM and " << maxValue << "RPM" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU fan speed range" << std::endl;

        // Get GPU VRAM range
        res = gpuMetricsSupport->GetGPUVRAMRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU VRAM range between " << minValue << "MB and " << maxValue << "MB" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU VRAM range" << std::endl;

        // Get GPU voltage range
        res = gpuMetricsSupport->GetGPUVoltageRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU voltage range between " << minValue << "mV and " << maxValue << "mV" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU voltage range" << std::endl;

        // Get GPU total board power range
        res = gpuMetricsSupport->GetGPUTotalBoardPowerRange(&minValue, &maxValue);
        if (ADLX_SUCCEEDED(res))
            std::cout << "The GPU total board power range between " << minValue << "W and " << maxValue << "W" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU total board power range" << std::endl;

        // Get GPU intake temperature range
        res = gpuMetricsSupport->GetGPUIntakeTemperatureRange (&minValue, &maxValue);
        if (ADLX_SUCCEEDED (res))
            std::cout << "The GPU intake temperature range between " << minValue << g_degree << "C and " << maxValue << g_degree << "C" << std::endl;
        else if (res == ADLX_NOT_SUPPORTED)
            std::cout << "Don't support GPU intake temperature range" << std::endl;
    }
}

// Display the system time stamp (in ms)
void GetTimeStampADL(IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_int64 timeStamp = 0;
    ADLX_RESULT res = gpuMetrics->TimeStamp(&timeStamp);
    if (ADLX_SUCCEEDED(res))
        std::cout << "The GPU time stamp is: " << timeStamp << "ms" << std::endl;
}

// Display GPU usage (in %)
void ShowGPUUsageADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU usage support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUUsage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU usage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double usage = 0;
            res = gpuMetrics->GPUUsage(&usage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU usage is: " << usage << "%" << std::endl;
        }
    }
}

// Function to get the GPU at a specific index
IADLXGPUPtr GetGPUDevice(adlx_uint index)
{
    ADLX_RESULT res = ADLX_FAIL;

    // Call the function to see if it's initialized ADLX
    if (!adlIsInitializedADL())
    {
        // ADLX initialization failed, return a default value or handle the error
        return nullptr;
    }

    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU list
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

        if (ADLX_SUCCEEDED(res) && index != gpus->End())
        {
            // Get the GPU at the specified index
            IADLXGPUPtr gpu;
            res = gpus->At(index, &gpu);

            if (ADLX_SUCCEEDED(res))
            {
                return gpu;
            }
            else
            {
                // Handle the error, you might want to log or throw an exception
                std::cerr << "Failed to get GPU at index " << index << std::endl;
            }
        }
        else
        {
            // Handle the error, you might want to log or throw an exception
            std::cerr << "Invalid GPU index or failed to get GPU list." << std::endl;
        }
    }
    else
    {
        // Handle the error, you might want to log or throw an exception
        std::cerr << "Failed to initialize ADLX." << std::endl;
    }

    // Return a nullptr in case of failure
    return nullptr;
}

// Function to get GPU metrics for a specific GPU
IADLXGPUMetricsPtr GetGPUMetricsADL(IADLXGPUPtr gpu)
{
    // Call the function to see if it's initialized ADLX
    if (!adlIsInitializedADL())
    {
        // ADLX initialization failed, return a default value or handle the error
        return nullptr;
    }
    
    ADLX_RESULT res = ADLX_FAIL;

    // Get Performance Monitoring services
    IADLXPerformanceMonitoringServicesPtr perfMonitoringServices;
    res = g_ADLXHelp.GetSystemServices()->GetPerformanceMonitoringServices(&perfMonitoringServices);

    if (ADLX_SUCCEEDED(res))
    {
        IADLXGPUMetricsPtr gpuMetrics;
        // Get current GPU metrics
        res = perfMonitoringServices->GetCurrentGPUMetrics(gpu, &gpuMetrics);

        if (ADLX_SUCCEEDED(res))
        {
            return gpuMetrics;
        }
    }

    // Handle the error, log, or throw an exception
    std::cerr << "Failed to get current GPU metrics." << std::endl;
    return nullptr; // Return nullptr to indicate failure
}

// Function to check GPU usage support status
bool adlIsGPUUsageSupportedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport)
{
    // Call the function to see if it's initialized ADLX
    if (!adlIsInitializedADL())
    {
        // ADLX initialization failed, return a default value or handle the error
        return false;
    }
    
    adlx_bool supported = false;
    // Check GPU usage support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUUsage(&supported);
    
    // Return true if the operation succeeded and GPU usage is supported
    return ADLX_SUCCEEDED(res) && supported;
}

// Function to get GPU usage (in %)
int adlGetGPUUsageADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
    
        adlx_bool supported = false;
    
        // Check GPU usage support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUUsage(&supported);
    
        if (ADLX_SUCCEEDED(res))
        {
            if (supported)
            {
                adlx_double usage = 0;
                res = gpuMetrics->GPUUsage(&usage);
                if (ADLX_SUCCEEDED(res))
                {
                    // Return GPU usage as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(usage);
                }
                return -1;
            }
            return -1;
        }
        return -1;
    }

    // Return a default value or an error code indicating failure
    return -1;
}

// Get GPU clock speed (in MHz)
int adlGetGPUClockSpeedADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;

        adlx_bool supported = false;
        // Check GPU clock speed support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUClockSpeed(&supported);

        if (ADLX_SUCCEEDED(res) && supported)
        {
            adlx_int gpuClock = 0;
            // Get GPU clock speed
            res = gpuMetrics->GPUClockSpeed(&gpuClock);
        
            if (ADLX_SUCCEEDED(res))
            {
                // Return GPU clock speed as an integer
                return static_cast<int>(gpuClock);
            }
        }
        return -1;
    }
    
    // Return a default value or an error code indicating failure
    return -1;
}

// Get GPU VRAM clock speed (in MHz)
int adlGetGPUVRAMClockSpeedADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;

        adlx_bool supported = false;
        // Check GPU VRAM clock speed support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAMClockSpeed(&supported);

        if (ADLX_SUCCEEDED(res) && supported)
        {
            adlx_int memoryClock = 0;
            // Get GPU VRAM clock speed
            res = gpuMetrics->GPUVRAMClockSpeed(&memoryClock);
        
            if (ADLX_SUCCEEDED(res))
            {
                // Return GPU VRAM clock speed as an integer
                return static_cast<int>(memoryClock);
            }
        }
        return -1;
    }

    // Return a default value or an error code indicating failure
    return -1;
}

// Display the system time stamp (in ms)
int adlGetTimeStampADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsPtr gpuMetrics;
    
        adlx_int64 timeStamp = 0;
        ADLX_RESULT res = gpuMetrics->TimeStamp(&timeStamp);
        if (ADLX_SUCCEEDED(res))
            {
            // Return the GPU timestamp as an integer
            return static_cast<int64>(timeStamp);
        } else {
            // Handle the error or return a default value as needed
            return -1;
        }
        return -1;
    }
    return -1;
}

// Display GPU temperature(in °C)
int adlGetGPUTemperatureADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU temperature support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTemperature(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_double temperature = 0;
                res = gpuMetrics->GPUTemperature(&temperature);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU temperature as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(temperature);
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

int adlGetGPUHotspotTemperatureADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU hotspot temperature support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUHotspotTemperature(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_double hotspotTemperature = 0;
                res = gpuMetrics->GPUHotspotTemperature(&hotspotTemperature);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU hotspot temperature as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(hotspotTemperature);
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

// Display GPU power(in W)
int adlGetGPUPowerADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU power support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUPower(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_double power = 0;
                res = gpuMetrics->GPUPower(&power);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU power as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(power);
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

// Display GPU total board power(in W)
int adlGetGPUTotalBoardPowerADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU total board power support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTotalBoardPower(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_double power = 0;
                res = gpuMetrics->GPUTotalBoardPower(&power);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU total board power as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(power);
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

int adlGetGPUIntakeTemperatureADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU intake temperature support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUIntakeTemperature(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_double temperature = 0;
                res = gpuMetrics->GPUIntakeTemperature(&temperature);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU intake temperature as an integer (you might want to round or convert to int as needed)
                    return static_cast<int>(temperature);
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

// Display GPU fan speed (in RPM)
int adlGetGPUFanSpeedInRPMADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;
        
        adlx_bool supported = false;

        // Check GPU fan speed support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUFanSpeed(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_int fanSpeed = 0;
                res = gpuMetrics->GPUFanSpeed(&fanSpeed);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU fan speed as an integer
                    return fanSpeed;
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

int adlGetGPUVRAMADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;

        adlx_bool supported = false;

        // Check GPU VRAM support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAM(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_int VRAM = 0;
                res = gpuMetrics->GPUVRAM(&VRAM);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU VRAM as an integer
                    return VRAM;
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

int adlGetGPUVoltageADL()
{
    if(adlIsInitializedADL())
    {
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        IADLXGPUMetricsPtr gpuMetrics;

        adlx_bool supported = false;

        // Check GPU voltage support status
        ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVoltage(&supported);
        if (ADLX_SUCCEEDED(res)) {
            if (supported) {
                adlx_int voltage = 0;
                res = gpuMetrics->GPUVoltage(&voltage);
                if (ADLX_SUCCEEDED(res)) {
                    // Return GPU voltage as an integer
                    return voltage;
                }
            }
        }
        // Handle the error or return a default value as needed
        return -1;
    }
    return -1;
}

// Get  GPU Count
int adlGetGPUDeviceCountADL()
{
    // Call the function to initialize ADLX
    if (!adlIsInitializedADL())
    {
        // ADLX initialization failed, return a default value or handle the error
        return -1;
    }

    // Get GPU list
    IADLXGPUListPtr gpus;
    ADLX_RESULT res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

    if (ADLX_SUCCEEDED(res))
    {
        // Iterate through the list to count GPUs
        int gpuCount = 0;
        for (int i = 0; i != gpus->End(); i++)
        {
            gpuCount++;
        }

        // Clean up ADLX before returning
        //ShutdownADL();

        return gpuCount;
    }
    else
    {
        // Handle the error, you might want to log or throw an exception
        std::cerr << "Failed to get GPU list" << std::endl;

        // Clean up ADLX before returning
        //ShutdownADL();

        return -1;
    }
}

// Display GPU clock speed (in MHz)
void ShowGPUClockSpeedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUClockSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU clock speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int gpuClock = 0;
            res = gpuMetrics->GPUClockSpeed(&gpuClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU clock speed is: " << gpuClock << "MHz" << std::endl;
        }
    }
}

// Display GPU VRAM clock speed (in MHz)
void ShowGPUVRAMClockSpeedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display the GPU VRAM clock speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAMClockSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU VRAM clock speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int memoryClock = 0;
            res = gpuMetrics->GPUVRAMClockSpeed(&memoryClock);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM clock speed is: " << memoryClock << "MHz" << std::endl;
        }
    }
}

// Display GPU temperature(in °C)
void ShowGPUTemperatureADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    // Display the GPU temperature support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU temperature support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double temperature = 0;
            res = gpuMetrics->GPUTemperature(&temperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU temperature is: " << temperature << g_degree <<"C" << std::endl;
        }
    }
}

// Display GPU hotspot temperature(in °C)
void ShowGPUHotspotTemperatureADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    // Display GPU hotspot temperature support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUHotspotTemperature(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU hotspot temperature support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double hotspotTemperature = 0;
            res = gpuMetrics->GPUHotspotTemperature(&hotspotTemperature);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU hotspot temperature is: " << hotspotTemperature << g_degree <<"C" << std::endl;
        }
    }
}

// Display GPU power(in W)
void ShowGPUPowerADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU power support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUPower(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU power support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->GPUPower(&power);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU power is: " << power << "W" << std::endl;
        }
    }
}

// Display GPU total board power(in W)
void ShowGPUTotalBoardPowerADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU total board power support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUTotalBoardPower(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU total board power support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double power = 0;
            res = gpuMetrics->GPUTotalBoardPower(&power);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU total board power is: " << power << "W" << std::endl;
        }
    }
}

// Display GPU intake temperature(in °C)
void ShowGPUIntakeTemperatureADL (IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;

    // Display the GPU temperature support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUIntakeTemperature (&supported);
    if (ADLX_SUCCEEDED (res))
    {
        std::cout << "GPU intake temperature support status: " << supported << std::endl;
        if (supported)
        {
            adlx_double temperature = 0;
            res = gpuMetrics->GPUIntakeTemperature (&temperature);
            if (ADLX_SUCCEEDED (res))
                std::cout << "The GPU intake temperature is: " << temperature << g_degree << "C" << std::endl;
        }
    }
}

// Display GPU fan speed (in RPM)
void ShowGPUFanSpeedADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU fan speed support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUFanSpeed(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU fan speed support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int fanSpeed = 0;
            res = gpuMetrics->GPUFanSpeed(&fanSpeed);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU fan speed is: " << fanSpeed << "RPM" << std::endl;
        }
    }
}

// Display GPU VRAM (in MB)
void ShowGPUVRAMADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU VRAM support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVRAM(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU VRAM support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int VRAM = 0;
            res = gpuMetrics->GPUVRAM(&VRAM);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU VRAM is: " << VRAM << "MB" << std::endl;
        }
    }
}

// Display GPU Voltage (in mV)
void ShowGPUVoltageADL(IADLXGPUMetricsSupportPtr gpuMetricsSupport, IADLXGPUMetricsPtr gpuMetrics)
{
    adlx_bool supported = false;
    // Display GPU voltage support status
    ADLX_RESULT res = gpuMetricsSupport->IsSupportedGPUVoltage(&supported);
    if (ADLX_SUCCEEDED(res))
    {
        std::cout << "GPU voltage support status: " << supported << std::endl;
        if (supported)
        {
            adlx_int voltage = 0;
            res = gpuMetrics->GPUVoltage(&voltage);
            if (ADLX_SUCCEEDED(res))
                std::cout << "The GPU voltage is: " << voltage << "mV" << std::endl;
        }
    }
}

// Display current GPU metrics
void ShowCurrentGPUMetricsADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    ADLX_RESULT res1 = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

    // Accumulate and display current metrics for each of 10 loops
    IADLXGPUMetricsPtr gpuMetrics;
    for (int i = 0; i < 10; ++i)
    {
        // Clear screen
        system("cls");
        // Get current GPU metrics
        ADLX_RESULT res2 = perfMonitoringServices->GetCurrentGPUMetrics(oneGPU, &gpuMetrics);

        // Display timestamp and GPU metrics
        if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
        {
            std::cout << "The current GPU metrics: " << std::endl;
            std::cout << std::boolalpha;  // Display boolean variable as true or false
            GetTimeStampADL(gpuMetrics);
            ShowGPUUsageADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUClockSpeedADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUVRAMClockSpeedADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUTemperatureADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUHotspotTemperatureADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUPowerADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUFanSpeedADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUVRAMADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUVoltageADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUTotalBoardPowerADL(gpuMetricsSupport, gpuMetrics);
            ShowGPUIntakeTemperatureADL (gpuMetricsSupport, gpuMetrics);
            std::cout << std::noboolalpha;
        }
        Sleep(1000);
    }

    MainMenuADL();
}

void ShowCurrentGPUMetricsFromHistoricalADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->ClearPerformanceMetricsHistory();
    if (ADLX_FAILED(res))
    {
        std::cout << "Clear historical data failed" << std::endl;
        return;
    }

    // Start tracking performance metrics
    res = perfMonitoringServices->StartPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Start tracking performance metrics failed" << std::endl;
        return;
    }

    // Get GPU metrics support
    IADLXGPUMetricsSupportPtr gpuMetricsSupport;
    ADLX_RESULT metricsSupportRet = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

    // Accumulate and display current metrics for each of 10 loops
    adlx_int startMs = 0;
    adlx_int stopMs = 0;
    for (int it = 0; it < 10; ++it)
    {
        // Clear screen
        system("cls");

        IADLXGPUMetricsListPtr gpuMetricsList;
        res = perfMonitoringServices->GetGPUMetricsHistory(oneGPU, startMs, stopMs, &gpuMetricsList);

        // Display all the GPU metrics in the list
        IADLXGPUMetricsPtr gpuMetrics;
        for (int i = gpuMetricsList->Begin(); i != gpuMetricsList->End(); ++i)
        {
            res = gpuMetricsList->At(i, &gpuMetrics);
            // Display timestamp and GPU metrics
            if (ADLX_SUCCEEDED(metricsSupportRet) && ADLX_SUCCEEDED(res))
            {
                std::cout << "The current GPU metrics: " << std::endl;
                std::cout << std::boolalpha;  // Display boolean variable as true or false
                GetTimeStampADL(gpuMetrics);
                ShowGPUUsageADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUClockSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMClockSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUTemperatureADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUHotspotTemperatureADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUPowerADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUFanSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVoltageADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUTotalBoardPowerADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUIntakeTemperatureADL(gpuMetricsSupport, gpuMetrics);
                std::cout << std::noboolalpha;
            }
            std::cout << std::endl;
        }

        Sleep(1000);
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->StopPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Stop tracking performance metrics failed" << std::endl;
    }

    MainMenuADL();
}

// Display historical GPU Metrics
void ShowHistoricalGPUMetricsADL(IADLXPerformanceMonitoringServicesPtr perfMonitoringServices, IADLXGPUPtr oneGPU)
{
    // Clear historical performance metrics data
    ADLX_RESULT res = perfMonitoringServices->ClearPerformanceMetricsHistory();
    if (ADLX_FAILED(res))
    {
        std::cout << "Clear historical data failed" << std::endl;
        return;
    }

    // Start tracking performance metrics
    res = perfMonitoringServices->StartPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Start tracking performance metrics failed" << std::endl;
        return;
    }

    // Wait for 10 seconds to accumulate metrics
    std::cout << "Wait for 10 seconds to accumulate metrics..." << std::endl;
    Sleep(10000);

    // Get GPU metrics history from 10 seconds ago(10000 ms: the second parameter) to the present time(0 ms: the third parameter)
    IADLXGPUMetricsListPtr gpuMetricsList;
    res = perfMonitoringServices->GetGPUMetricsHistory(oneGPU, 10000, 0, &gpuMetricsList);
    if (ADLX_SUCCEEDED(res))
    {
        // Get GPU metrics support
        IADLXGPUMetricsSupportPtr gpuMetricsSupport;
        ADLX_RESULT res1 = perfMonitoringServices->GetSupportedGPUMetrics(oneGPU, &gpuMetricsSupport);

        // Display all the GPU metrics in the list
        IADLXGPUMetricsPtr gpuMetrics;
        for (int i = gpuMetricsList->Begin(); i != gpuMetricsList->End(); ++i)
        {
            std::cout << "********** historical GPU metrics " << i + 1 << ": **********" << std::endl;
            ADLX_RESULT res2 = gpuMetricsList->At(i, &gpuMetrics);
            // Display timestamp and GPU metrics
            if (ADLX_SUCCEEDED(res1) && ADLX_SUCCEEDED(res2))
            {
                std::cout << std::boolalpha;  // Display boolean variable as true or false
                GetTimeStampADL(gpuMetrics);
                ShowGPUUsageADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUClockSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMClockSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUTemperatureADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUHotspotTemperatureADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUPowerADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUFanSpeedADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVRAMADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUVoltageADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUTotalBoardPowerADL(gpuMetricsSupport, gpuMetrics);
                ShowGPUIntakeTemperatureADL(gpuMetricsSupport, gpuMetrics);
                std::cout << std::noboolalpha;
            }
            std::cout << std::endl;
        }
    }

    // Stop tracking performance metrics
    res = perfMonitoringServices->StopPerformanceMetricsTracking();
    if (ADLX_FAILED(res))
    {
        std::cout << "Stop tracking performance metrics failed" << std::endl;
        return;
    }
}