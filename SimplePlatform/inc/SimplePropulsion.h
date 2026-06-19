#pragma once
#include "IPropulsion.h"
#include "IStatelessModel.h"
#include "Vector3D.h"

class SimplePropulsion : public IPropulsion, public IStatelessModel
{
public:

	SimplePropulsion(IPhysicalPlatform* platform);

	Vector3D GetPropulsiveForceBody(double time) override;

	// r x F + Spool Moment
	Vector3D GetPropulsiveMomentAtCG(double time) const override;

	double GetMassFlowRate(double time) const override;

	// Angular Momentum (I x w) of rotating discs
	Vector3D GetAngularMomentum() const override;
};

