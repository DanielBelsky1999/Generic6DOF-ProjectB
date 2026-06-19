#pragma once
#include "IPhysicalModel.h"
#include "Matrix33.h"
#include "Vector3D.h"

class IPhysicalPlatform;

class IMassInertia : public IPhysicalModel
{
public:
	IMassInertia(IPhysicalPlatform* platform);

	virtual double GetMass(double time) const = 0;
	virtual Matrix33 GetInertiaCG(double time) const = 0;
	virtual Matrix33 GetInertiaInverse(double time) const = 0;
	virtual Vector3D CG(double time) const = 0;
};

