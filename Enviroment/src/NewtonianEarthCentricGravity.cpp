#include "NewtonianEarthCentricGravity.h"

Vector3D NewtonianEarthCentric::GetGravityAccelerationNED(const Vector3D& positionECEF)
{
    double r = positionECEF.Norm();
    Vector3D gravity_accel_ecef = (-G * M_Earth / (r * r * r)) * positionECEF;
    Vector3D llh = NavigationUtils::ECEF_to_LLH(positionECEF);
    Quaternion q_en = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
    Vector3D gravity_accel_NED = ImaginaryFromQuaternion(q_en.Conjugate() * gravity_accel_ecef * q_en);
    return gravity_accel_NED;
}
