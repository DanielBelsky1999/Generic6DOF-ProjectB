#include "NewtonianNormal.h"

Vector3D NewtonianNormal::GetGravityAccelerationNED(const Vector3D& positionECEF)
{
    double r = positionECEF.Norm();
    double gravity_accel = (G * M_Earth / (r * r));
    return Vector3D(0,0, gravity_accel);
}
