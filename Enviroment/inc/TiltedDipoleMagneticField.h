#pragma once
#include "IMagneticField.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Constants.h"
#include "nav_math_operators.h"
#include "LinearAlgebraOps.h"
#include "NavigationUtils.h"

class TiltedDipoleMagneticField : public IMagneticField
{
public:
	TiltedDipoleMagneticField();
	Vector3D GetMagneticField_sensor(const Vector3D& llh, const Quaternion& q_ns) override;
private:
	Vector3D m;
};

