#pragma once
#include "IGravity.h"

/// <summary>
/// Intended to be used only by FlatEarthKinematics
/// </summary>
class NoGravity : public IGravity
{
public:
	Vector3D GetGravityAccelerationNED(const Vector3D& position) override { return Vector3D(); };
};

