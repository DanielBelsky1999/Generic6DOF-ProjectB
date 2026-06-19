#pragma once
#include "IGravity.h"

class NewtonianEarthCentric : public IGravity
{
public:
	Vector3D GetGravityAccelerationNED(const Vector3D& position) override;

private:
	static constexpr double G = 6.67430e-11;
	static constexpr double M_Earth = 5.97219e24;

};

