#pragma once
#include "IMagneticField.h"

class NoneMagneticField : public IMagneticField 
{
public:
	Vector3D GetMagneticField_sensor(const Vector3D& llh, const Quaternion& q_ns) override { return Vector3D(); };
};