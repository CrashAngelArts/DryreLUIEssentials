// Copyright © 2024 - DryreL Design

#pragma once

#include "Modules/ModuleManager.h"

class FDryreLUIEssentialsPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

};
