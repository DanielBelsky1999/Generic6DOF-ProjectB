#include "SimplePropulsion.h"
#include "SimplePlatformControls.h"

SimplePropulsion::SimplePropulsion(IPhysicalPlatform* platform)
	: IPropulsion(platform)
{
}

Vector3D SimplePropulsion::GetPropulsiveForceBody(double time)
{
	SimplePlatformControls& controls = static_cast<SimplePlatformControls&>(GetControls());
	if (controls.ignition) { // Note - you must be using this kind of flag to prevent integrators using "data from the future"
		if (time > 20.0 && time < 40.0)
			return Vector3D(100.0, 0, 0);
	}
	return Vector3D();
}

Vector3D SimplePropulsion::GetPropulsiveMomentAtCG(double time) const
{
	return Vector3D();
}

double SimplePropulsion::GetMassFlowRate(double time) const
{
	return 0.0;
}

Vector3D SimplePropulsion::GetAngularMomentum() const
{
	return Vector3D();
}
