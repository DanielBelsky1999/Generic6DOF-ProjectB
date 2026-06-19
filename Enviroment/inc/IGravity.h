#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "nav_math_operators.h"
#include "NavigationUtils.h"

class IGravity
{
public:
	virtual Vector3D GetGravityAccelerationNED(const Vector3D& position) = 0;
};

