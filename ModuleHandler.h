/*-------------------------------------------------------------------------------

Author : Ivar Jönsson
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

	void SetHeight();
	void SetWidth();
	void SetRow();

	int GetRandom();

	SProperties *GetProperties() { return &sProperties; }

protected:

	std::vector<string> Models = 
	{ 
		"Objects/Modules/apartment/wall_budge_window.cgf", 
		"Objects/Modules/apartment/wall.cgf",
		"Objects/Modules/apartment/wall_buldge.cgf",
		"Objects/Modules/apartment/window_wide.cgf",
		"Objects/Modules/apartment/window_thin.cgf",

	};

	std::vector<int> HeightVec = {};
	std::vector<int> WidthVec = {};

	Vec3 HeightOffset = Vec3(0, 0, 0);
	Vec3 HeightLastOffset = Vec3(0, 0, 0);

	Vec3 WidthOffset = Vec3(0, 0, 0);
	Vec3 WidthLastOffset = Vec3(0, 0, 0);

	int slotCount = 0;

	int LastWidth = 0;
	int LastHeight = 0;

	SProperties sProperties;

};