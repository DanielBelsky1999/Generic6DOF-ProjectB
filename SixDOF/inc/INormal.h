#pragma once
#include "IPhysicalModel.h"
#include "Vector3D.h"

class INormal : public IPhysicalModel
{
public:
	INormal(IPhysicalPlatform* platform);

	virtual Vector3D GetNormalBody(double time) = 0;
};

