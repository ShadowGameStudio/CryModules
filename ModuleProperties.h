#pragma once

#include "StdAfx.h"

enum EBuildingType {

	eBT_ApartmentBuilding

};

static void ReflectType(Schematyc::CTypeDesc<EBuildingType>& desc) {

	desc.SetGUID("{6463B9DA-E5A8-4950-B0E6-AE3394BA4C9F}"_cry_guid);
	desc.SetLabel("Building Type");
	desc.SetDescription("Choose the buildings type");
	desc.SetFlags(Schematyc::ETypeFlags::Switchable);
	desc.SetDefaultValue(EBuildingType::eBT_ApartmentBuilding);
	desc.AddConstant(EBuildingType::eBT_ApartmentBuilding, "ApartmentBuilding", "Apartment Building");

}

enum EBuildingVersion {

	eBV_Old,
	eBV_New

};

static void ReflectType(Schematyc::CTypeDesc<EBuildingVersion>& desc) {

	desc.SetGUID("{C08B548C-888D-4DDC-975B-E83F24BDC1FF}"_cry_guid);
	desc.SetLabel("Building Version");
	desc.SetDescription("Sets the version on the building");
	desc.SetFlags(Schematyc::ETypeFlags::Switchable);
	desc.SetDefaultValue(EBuildingVersion::eBV_New);
	desc.AddConstant(EBuildingVersion::eBV_New, "New", "New");
	desc.AddConstant(EBuildingVersion::eBV_Old, "Old", "Old");

}

struct SProperties {

	inline bool operator==(const SProperties &rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SProperties &rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	int ModuleCountWidth;
	int ModuleCountHeight;
	bool bHasIndoor;
	EBuildingVersion eBuildingVersion;
	EBuildingType eBuildingType;

};

static void ReflectType(Schematyc::CTypeDesc<SProperties>& desc) {

	desc.SetGUID("{225C5BDD-FDA2-4F88-B418-CECF704DA4A4}"_cry_guid);
	desc.SetLabel("Module properties");
	desc.SetDescription("Sets all of the different module properties");
	desc.AddMember(&SProperties::ModuleCountWidth, 'mwit', "ModuleCountWidth", "ModuleCountWidth", "Sets the width of the building", 0);
	desc.AddMember(&SProperties::ModuleCountHeight, 'mhei', "ModuleCountHeight", "ModuleCountHeight", "Sets the height of the building", 0);
	desc.AddMember(&SProperties::bHasIndoor, 'bhi', "HasIndoor", "Has Indoor", "Sets whether the object should have indoor or not", false);
	desc.AddMember(&SProperties::eBuildingVersion, 'ebv', "BuildingVersion", "Building Version", "Sets the building version", EBuildingVersion());
	desc.AddMember(&SProperties::eBuildingType, 'ebt', "BuildingType", "Buildning Type", "Sets the buildings type", EBuildingType());

}