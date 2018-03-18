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
	virtual void ProcessEvent(SEntityEvent& event) override;
	static void ReflectType(Schematyc::CTypeDesc<CModuleComponent>& desc);

	void LoadGeometry();
	void Physicalize();

	SProperties *GetProperties() { return &sProperties; }

protected:

	SProperties sProperties;

};