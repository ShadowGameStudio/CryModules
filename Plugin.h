#pragma once

#include <CrySystem/ICryPlugin.h>

#include <CryGame/IGameFramework.h>

#include <CryEntitySystem/IEntityClass.h>

class CPlugin 
	: public Cry::IEnginePlugin
	, public ISystemEventListener
{
public:
	CRYINTERFACE_SIMPLE(Cry::IEnginePlugin)
	CRYGENERATE_SINGLETONCLASS_GUID(CPlugin, "CryModules", "2711a23d-3848-4cdd-a95b-e9d88ffa23b0"_cry_guid)

	virtual ~CPlugin();

	//! This is called to initialize the new plugin.
	virtual bool Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;

	// ISystemEventListener
	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener
};