#pragma once
#include "IPhysicalModel.h"
#include "Vector3D.h"

class IPhysicalPlatform;

class IPropulsion : public IPhysicalModel
{
public:
	IPropulsion(IPhysicalPlatform* platform);

	virtual Vector3D GetPropulsiveForceBody(double time) = 0;
	virtual Vector3D GetPropulsiveMomentAtCG(double time) const = 0;
	virtual double GetMassFlowRate(double time) const = 0;
	virtual Vector3D GetAngularMomentum() const = 0;

};

