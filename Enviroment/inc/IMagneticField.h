#pragma once

#include "Vector3D.h"
#include "Quaternion.h"

class IMagneticField {
public:
	// returns: field vector in [Tesla]
	virtual Vector3D GetMagneticField_sensor(const Vector3D& llh, const Quaternion& q_ns) = 0;
};