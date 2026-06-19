#pragma once
#include "SimplePlatformControls.h"
#include "IPhysicalPlatform.h"
#include "SimpleAerodynamics.h"
#include "SimpleMassInertia.h"
#include "SimplePropulsion.h"
#include "SimpleActuators.h"
#include "SimpleNormal.h"


class SimplePlatform : public IPhysicalPlatform
{
public:
	SimplePlatform(TControls* controls);
private:
	// todo These will later become unique_ptrs that will be std::move'd to IPhysicalPlatform's responsibility
	SimpleAerodynamics* sAerodynamics;
	SimpleMassInertia* sMassInertia;
	SimplePropulsion* sPropulsion;
	SimpleActuators* sActuators;
	SimpleNormal* sNormal;
};

