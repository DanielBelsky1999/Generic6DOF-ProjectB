#pragma once
#include "IAerodynamics.h"
#include "IStatelessModel.h"
#include "Vector3D.h"

class SimpleAerodynamics : public IAerodynamics, public IStatelessModel
{
public:
	SimpleAerodynamics(IPhysicalPlatform* platform);

	Vector3D GetAeroForceBody() override;
	Vector3D GetAeroMomentAtCG() override;
};

