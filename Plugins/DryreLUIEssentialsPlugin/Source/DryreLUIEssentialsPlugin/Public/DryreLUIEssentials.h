// Copyright © 2024 - DryreL Design

#include "Modules/ModuleManager.h"
#include "DryreLUIEssentialsBPLibrary.h"
#include "Interfaces/IPluginManager.h"
//#include "NVMLManager.h"
//#include "ADLManager.h"
#include "../Source/ThirdParty/NVML/generate_library/NVMLManager.h"
#include "../Source/ThirdParty/ADL/generate_library/ADLManager.h"

#pragma once

class FDryreLUIEssentialsPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Handle to the test dll we will load */
	void*	LibraryHandle;
};
