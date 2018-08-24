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

	float GetUnitHeight() { return (float)(GetHeight() * 3); }
	float GetUnitWidth() { return (float)(GetWidth() * 2) - 2; }

	EModelType GetBuildingType() { return GetProperties()->eModelType; }
	EModelVersion GetBuildingVersion() { return GetProperties()->eModelVersion; }

	void LoadGeometry();
	void Physicalize();
	void GetModelsFromXML();
	void SetBuildingSettings();

	void SetHeight();
	void SetWidth();
	void SetRow();

	int GetRandom();

	SProperties *GetProperties() { return &sProperties; }

protected:

	std::vector<XmlString> Models = {};

	std::vector<int> HeightVec = {};
	std::vector<int> WidthVec = {};

	int slotCount = 0;

	int LastWidth = 0;
	int LastHeight = 0;

	string sModelType;
	string sModelVersion;

	SProperties sProperties;

};