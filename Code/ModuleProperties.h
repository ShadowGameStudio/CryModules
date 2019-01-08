#pragma once

#include "StdAfx.h"

enum EModelType {

	eMT_ApartmentBuilding

};

static void ReflectType(Schematyc::CTypeDesc<EModelType>& desc) {

	desc.SetGUID("{6463B9DA-E5A8-4950-B0E6-AE3394BA4C9F}"_cry_guid);
	desc.SetLabel("Building Type");
	desc.SetDescription("Choose the buildings type");
	desc.SetFlags(Schematyc::ETypeFlags::Switchable);
	desc.SetDefaultValue(EModelType::eMT_ApartmentBuilding);
	desc.AddConstant(EModelType::eMT_ApartmentBuilding, "ApartmentBuilding", "Apartment Building");

}

enum EModelVersion {

	eMV_Old,
	eMV_New

};

static void ReflectType(Schematyc::CTypeDesc<EModelVersion>& desc) {

	desc.SetGUID("{C08B548C-888D-4DDC-975B-E83F24BDC1FF}"_cry_guid);
	desc.SetLabel("Building Version");
	desc.SetDescription("Sets the version on the building");
	desc.SetFlags(Schematyc::ETypeFlags::Switchable);
	desc.SetDefaultValue(EModelVersion::eMV_New);
	desc.AddConstant(EModelVersion::eMV_New, "New", "New");
	desc.AddConstant(EModelVersion::eMV_Old, "Old", "Old");

}

struct SProperties {

	inline bool operator==(const SProperties &rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SProperties &rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	int ModuleCountWidth;
	int ModuleCountHeight;
	bool bHasIndoor;
	EModelVersion eModelVersion;
	EModelType eModelType;

};

static void ReflectType(Schematyc::CTypeDesc<SProperties>& desc) {

	desc.SetGUID("{225C5BDD-FDA2-4F88-B418-CECF704DA4A4}"_cry_guid);
	desc.SetLabel("Module properties");
	desc.SetDescription("Sets all of the different module properties");
	desc.AddMember(&SProperties::ModuleCountWidth, 'mwit', "ModuleCountWidth", "ModuleCountWidth", "Sets the width of the building", 0);
	desc.AddMember(&SProperties::ModuleCountHeight, 'mhei', "ModuleCountHeight", "ModuleCountHeight", "Sets the height of the building", 0);
	desc.AddMember(&SProperties::bHasIndoor, 'bhi', "HasIndoor", "Has Indoor", "Sets whether the object should have indoor or not", false);
	desc.AddMember(&SProperties::eModelVersion, 'ebv', "BuildingVersion", "Building Version", "Sets the building version", EModelVersion());
	desc.AddMember(&SProperties::eModelType, 'ebt', "BuildingType", "Buildning Type", "Sets the buildings type", EModelType());

}