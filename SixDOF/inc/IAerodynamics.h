#pragma once
#include "IPhysicalModel.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "nav_math_operators.h"
#include "LinearAlgebraOps.h"

class IPhysicalPlatform;

class IAerodynamics : public IPhysicalModel
{
public:
	IAerodynamics(IPhysicalPlatform* platform);

	virtual Vector3D GetAeroForceBody() = 0;
	virtual Vector3D GetAeroMomentAtCG() = 0;
	Vector3D GetVelocityBody();

protected:
	double GetAOA();
	double GetBeta();

};

