#include "StdAfx.h"
#include "ModuleHandler.h"
#include "ModuleProperties.h"

#include <iostream>

#include <CryEntitySystem\IEntityComponent.h>
#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CrySchematyc\Env\Elements\EnvComponent.h>
#include <CrySystem/ISystem.h>

static void RegisterEntityComponent(Schematyc::IEnvRegistrar& registrar) {
	Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
	{
		Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(CModuleComponent));
		// Functions
		{
		}
	}
}

CRY_STATIC_AUTO_REGISTER_FUNCTION(&RegisterEntityComponent)

void CModuleComponent::Initialize() {

	//Makes sure that there isn't any slots in the entity
	m_pEntity->ClearSlots();
	GetModelsFromXML();

}

uint64 CModuleComponent::GetEventMask() const {
	return ENTITY_EVENT_BIT(ENTITY_EVENT_EDITOR_PROPERTY_CHANGED);
}

void CModuleComponent::ProcessEvent(const SEntityEvent & event) {

	switch (event.event) {
	case ENTITY_EVENT_EDITOR_PROPERTY_CHANGED:
		{

		//When the editor properties has changed, reload the geom and physicalize it
		GetModelsFromXML();
		LoadGeometry();
		Physicalize();

		}
		break;
	}

}

void CModuleComponent::ReflectType(Schematyc::CTypeDesc<CModuleComponent>& desc) {

	desc.SetGUID("{73B27C98-03E5-4C51-8712-7E260FEA303C}"_cry_guid);
	desc.SetLabel("CryModules");
	desc.SetEditorCategory("Tools");
	desc.SetComponentFlags({ IEntityComponent::EFlags::Transform, IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach });
	desc.AddMember(&CModuleComponent::sProperties, 'spro', "Properties", "Properties", "Sets the different properties for the module", SProperties());

}

//Loads the geometry that is needed for the building
void CModuleComponent::LoadGeometry() {

	if (GetHeight() != 0) {
		
		if (GetHeight() != LastHeight) {

			//Sets the height
			SetHeight();

		}
	
	}

	if (GetWidth() != 0) {

		if (GetWidth() != LastWidth) {
			
			//Sets the width
			SetWidth();
			SetRow();

		}

	}

}

//Physiscalizes the building
void CModuleComponent::Physicalize() {

	SEntityPhysicalizeParams physParams;
	physParams.type = PE_STATIC;
	m_pEntity->Physicalize(physParams);

}

void CModuleComponent::GetModelsFromXML() {

	//If it can get the XML file, continue
	if (XmlNodeRef rootNode = gEnv->pSystem->LoadXmlFromFile("ModelsXML.xml", false)) {

		//Get every child from the root node
		for (int i = 0, n = rootNode->getChildCount(); i < n; i++) {

			//Get the child
			XmlNodeRef childNode = rootNode->getChild(i);
			bool value = false;

			//Get the modelVersion attribute
			XmlString modelVer;
			if (childNode->getAttr("modelVersion", modelVer)) {

				//If the modelVer attribute and the building version is "New"
				if (modelVer == "New" || GetProperties()->eBuildingVersion == eBV_New) {
					
					//Get the modelType attribute
					XmlString modelType;
					if (childNode->getAttr("modelType", modelType)) {
						
						//If the modelType attribute and the building type is "ApartmentBuilding"
						if (modelType == "apartmentBuilding" || GetProperties()->eBuildingType == eBT_ApartmentBuilding) {

							//Get the modelPath attribute
							XmlString modelPath;
							if (childNode->getAttr("modelPath", modelPath)) {
								//Add the model path to the vector
								Models.push_back(modelPath);

							}

						}

					}

				}
				//If the modelVer instead is old, continue
				else if (modelVer == "Old" || GetProperties()->eBuildingVersion == eBV_New) {

					//Get the modelType
					XmlString modelType;
					if (childNode->getAttr("modelType", modelType)) {

						//If the modelType and the BuildingType is apartmentBuilding, continue
						if (modelType == "apartmentBuilding" || GetProperties()->eBuildingType == eBT_ApartmentBuilding) {

							//Get the modelPath
							XmlString modelPath;
							if (childNode->getAttr("modelPath", modelPath)) {
								//Add the path to the vector
								Models.push_back(modelPath);
							}

						}

					}

				}

			}

		}

	}
	else {
		//If the file could not be loaded, give a warning
		CryLogAlways("ModelsXML could not be loaded!");
	}

}

void CModuleComponent::SetHeight() {

	//Matrix and Vector3 for the slot offset
	//Get the model to apply
	//Set the slot used for the geometry
	Matrix34 maOffset = IDENTITY;
	const Vec3 HeightOffset = Vec3(0, 0, GetUnitHeight());
	const string sModelPath = Models[GetRandom()];
	const int slot = m_pEntity->GetSlotCount();
	
	//Apply the offset to the Matrix
	maOffset.SetTranslation(HeightOffset);

	//Apply the model and the offset
	m_pEntity->LoadGeometry(slot, sModelPath);
	m_pEntity->SetSlotLocalTM(slot, maOffset);

	//Adds the slot to a vector that holds all the slots
	HeightVec.push_back(slot);

	//Sets the last height to the current
	LastHeight = GetHeight();

	string out = ToString(m_pEntity->GetSlotCount());
	CryLogAlways(out);
}

void CModuleComponent::SetWidth() {

	//Matrix and Vector3 for the slot offset
	//Get the model to apply
	Matrix34 maOffset = IDENTITY;
	const Vec3 WidthOffset = Vec3(GetUnitWidth(), 0, 0);
	const string sModelPath = Models[GetRandom()];

	//Apply the offset to the Matrix
	maOffset.SetTranslation(WidthOffset);

	//If the ModuleWidth is one, continue
	if (GetWidth() == 1) {

		//The slot used to attach the geometry
		const int slot = 0;

		//Because the ModuleWidth is one, the translation will be zero
		maOffset.SetTranslation(Vec3(0, 0, 0));

		//Load the geometry to the correct slot
		//Apply the offset to the slot
		m_pEntity->LoadGeometry(slot, sModelPath);
		m_pEntity->SetSlotLocalTM(slot, maOffset);

		//Add the slot to the slot vector
		//So that we know that we are which slots we are using for what
		WidthVec.push_back(slot);

	}
	//If it's not, continue
	else {

		//The slot used to attach the geometry
		const int slot = m_pEntity->GetSlotCount();

		//Load the geometry to the correct slot
		//Apply the offset to the slot
		m_pEntity->LoadGeometry(slot, sModelPath);
		m_pEntity->SetSlotLocalTM(slot, maOffset);

		//Add the slot to the slot vector
		//So that we know that we are which slots we are using for what
		WidthVec.push_back(slot);

	}

	//Sets the last width to the current width
	LastWidth = GetWidth();

	string out = ToString(m_pEntity->GetSlotCount());
	CryLogAlways(out);

}

void CModuleComponent::SetRow() {

	//If the module width is greater than one, continue
	if (GetWidth() >= 1 && GetHeight() >= 1) {

		float unitWidth = GetUnitWidth();

		for (int i = 0; i < GetHeight(); i++) {

			while (unitWidth > 0) {

				Matrix34 mPos = m_pEntity->GetSlotLocalTM(HeightVec[i], false);
				Vec3 vPos = mPos.GetTranslation();
				const string sModelPath = Models[GetRandom()];

				const int slot = m_pEntity->GetSlotCount();

				Matrix34 maOffset = IDENTITY;
				maOffset.SetTranslation(Vec3(unitWidth, 0, vPos.z));

				m_pEntity->LoadGeometry(slot, sModelPath);
				m_pEntity->SetSlotLocalTM(slot, maOffset);

				unitWidth -= 2;

				break;

			}
		}

		string out = ToString(m_pEntity->GetSlotCount());
		CryLogAlways(out);

	}

}

int CModuleComponent::GetRandom() {

	srand((unsigned int)time(NULL));

	//Get a random number between zero and the last entry to the vector
	int random = rand() % Models.size();

	//return the number
	return random;

}


