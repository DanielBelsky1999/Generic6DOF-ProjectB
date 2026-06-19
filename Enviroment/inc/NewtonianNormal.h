#pragma once
#include "IGravity.h"

/// <summary>
/// A simple normal model with a magnitude that acts newtonian-like ( decreases with the square of latitude),
/// but acts in the local normal direction (as opposed to Earth-centric direction)
/// </summary>
class NewtonianNormal : public IGravity
{
public:
	Vector3D GetGravityAccelerationNED(const Vector3D& positionECEF) override;
private:
	static constexpr double G = 6.67430e-11;
	static constexpr double M_Earth = 5.97219e24;
};

