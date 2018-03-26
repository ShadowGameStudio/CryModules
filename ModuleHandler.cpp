#include "StdAfx.h"
#include "ModuleHandler.h"
#include "ModuleProperties.h"

#include <CryEntitySystem\IEntityComponent.h>
#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CrySchematyc\Env\Elements\EnvComponent.h>

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

	LoadGeometry();
	Physicalize();

}

uint64 CModuleComponent::GetEventMask() const {
	return ENTITY_EVENT_BIT(ENTITY_EVENT_EDITOR_PROPERTY_CHANGED);
}

void CModuleComponent::ProcessEvent(const SEntityEvent & event) {

	switch (event.event) {
	case ENTITY_EVENT_EDITOR_PROPERTY_CHANGED:
		{

		//When the editor properties has changed, reload the geom and physicalize it
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
			
			if (GetHeight() < LastHeight) {

				//Get the slot to free(the last added)
				int slot = HeightVec.back();
				//Frees the slot
				m_pEntity->FreeSlot(slot);

				//Remove the last added slot
				HeightVec.erase(HeightVec.end());
				//Set the last height to the current
				LastHeight = GetHeight();

			}
			else {
				
				//Sets the height
				SetHeight();

			}


		}
	
	}

	if (GetWidth() != 0) {

		if (GetWidth() != LastWidth) {
			
			if (GetWidth() < LastWidth) {

				//Get the slot to free(the last added)
				int slot = WidthVec.back();
				//Frees the slot
				m_pEntity->FreeSlot(slot);

				//Remove the last added slot
				WidthVec.erase(WidthVec.end());
				//Set the last width to the current
				LastWidth = GetWidth();

			}
			else {
				
				SetWidth();

			}

		}

	}

}

//Physiscalizes the building
void CModuleComponent::Physicalize() {

	SEntityPhysicalizeParams physParams;
	physParams.type = PE_STATIC;
	m_pEntity->Physicalize(physParams);

}

void CModuleComponent::SetHeight() {

	//Set the offset to the last offset + three
	HeightOffset = HeightLastOffset + Vec3(0, 0, 3);
	//Create a matrix for the offset
	Matrix34 maOffset = IDENTITY;
	//Set teh offset
	maOffset.SetTranslation(HeightOffset);
	//Sets the string for the model location
	string sModelPath = Models[GetRandom()];

	//Create the slot int
	int slot = 0;
	//If the slot count is zero, continue
	if (m_pEntity->GetSlotCount() == 0) {
		//Set the slot to zero
		slot = 0;

	}
	//Else if the slot is more than zero, continue
	else {
		//Set the slot to the slotcount plus one
		slot = m_pEntity->GetSlotCount() + 1;
	}

	//Sets the model
	m_pEntity->LoadGeometry(slot, sModelPath);
	//Sets the slot offset
	m_pEntity->SetSlotLocalTM(slot, maOffset);

	//Adds the slot to a vector that holds all the slots
	HeightVec.push_back(slot);
	//Sets the last offset to the current
	HeightLastOffset = HeightOffset;

	LastHeight = GetHeight();
}

void CModuleComponent::SetWidth() {

	//Set the offset to the last offset + two
	WidthOffset = WidthLastOffset + Vec3(2, 0, 0);
	//Create a matrix for the offset
	Matrix34 maOffset = IDENTITY;
	//Set the offset
	maOffset.SetTranslation(WidthOffset);
	//Gets the string for the model location
	string sModelPath = Models[GetRandom()];
	//Get the slot to put it in
	const int slot = m_pEntity->GetSlotCount() + 1;
	//Sets the model
	m_pEntity->LoadGeometry(slot, sModelPath);
	//Sets the slot offset
	m_pEntity->SetSlotLocalTM(slot, maOffset);

	//Adds the slot to a vector that holds all the slots
	WidthVec.push_back(slot);
	//Set the last offset to the current
	WidthLastOffset = WidthOffset;

	LastWidth = GetWidth();

}

int CModuleComponent::GetRandom() {

	srand((unsigned int)time(NULL));

	//Get a random number between zero and the last entry to the vector
	int random = rand() % Models.size();
	//return the number
	return random;

}


