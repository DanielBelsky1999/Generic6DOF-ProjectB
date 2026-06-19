#include "ConstantEarthCentricGravity.h"

Vector3D ConstantEarthCentricGravity::GetGravityAccelerationNED(const Vector3D& positionECEF)
{
    Vector3D gravity_accel_ecef = -9.81 * positionECEF / positionECEF.Norm();

    Vector3D llh = NavigationUtils::ECEF_to_LLH(positionECEF);
    Quaternion q_en = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
    Vector3D gravity_accel_NED = ImaginaryFromQuaternion(q_en.Conjugate() * gravity_accel_ecef * q_en);

    return gravity_accel_NED;
}
