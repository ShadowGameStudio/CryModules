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

	string sGeomPath = "Objects/Default/primitive_sphere.cgf";
	string sGeomPathT = "Objects/Default/primitive_cube.cgf";

	m_pEntity->LoadGeometry(GEOM_SLOT_1, sGeomPath);
	m_pEntity->LoadGeometry(GEOM_SLOT_2, sGeomPathT);

}

//Physiscalizes the building
void CModuleComponent::Physicalize() {}


