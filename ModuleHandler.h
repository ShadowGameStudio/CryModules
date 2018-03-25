/*-------------------------------------------------------------------------------

Author : Ivar J�nsson
Project : CryModules
Purpose : Handels all of the main module functionality

-------------------------------------------------------------------------------*/

#pragma once

#include <CryEntitySystem/IEntityComponent.h>
#include "ModuleProperties.h"

class CModuleComponent final : public IEntityComponent {

public:
	CModuleComponent() = default;

	virtual void Initialize() override;
	virtual uint64 GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event) override;
	static void ReflectType(Schematyc::CTypeDesc<CModuleComponent>& desc);

	int GetWidth() { return GetProperties()->ModuleCountWidth; }
	int GetHeight() { return GetProperties()->ModuleCountHeight; }

	EBuildingType GetBuildingType() { return GetProperties()->eBuildingType; }
	EBuildingVersion GetBuildingVersion() { return GetProperties()->eBuildingVersion; }

	void LoadGeometry();
	void Physicalize();

	SProperties *GetProperties() { return &sProperties; }

protected:

	SProperties sProperties;

};