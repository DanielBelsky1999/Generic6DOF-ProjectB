#pragma once
#include "IGravity.h"
class ConstantEarthCentricGravity : public IGravity
{
public:
	Vector3D GetGravityAccelerationNED(const Vector3D& position) override;
};

