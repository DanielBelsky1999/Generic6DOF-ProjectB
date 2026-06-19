#include "SimpleNormal.h"
#include "ECEFKinematics.h"
#include "Enviroment.h"
#include "IMassInertia.h"
#include "IPropulsion.h"
#include "IAerodynamics.h"

SimpleNormal::SimpleNormal(IPhysicalPlatform* platform)
    : INormal(platform)
{

}

Vector3D SimpleNormal::GetNormalBody(double time)
{
    Vector3D position = GetKinematics().GetPosition();

    Quaternion qnb = GetKinematics().GetQNB();

    Vector3D aero_and_propulsion_force_body = GetPropulsion().GetPropulsiveForceBody(time) + GetAerodynamics().GetAeroForceBody();
    // find other forces in NED D:
    Vector3D aero_and_propulsion_force_NED = ImaginaryFromQuaternion(qnb * aero_and_propulsion_force_body * qnb.Conjugate());

    Vector3D gravity_accel_NED = GetEnviroment().Gravity().GetGravityAccelerationNED(position);

    double mass = GetMassInertia().GetMass(time);

    static double InitialHeight = GetKinematics().GetAltitude();
    static bool deactivation_trigger = false;
    if ((fabs(GetKinematics().GetAltitude() - InitialHeight) > (D_EPS)) || ((gravity_accel_NED[2] + aero_and_propulsion_force_NED[2] / mass) < 0)) {

        deactivation_trigger = true;
    }
    if (deactivation_trigger) {
        return Vector3D();
    }

    // reconstruct the needed normal to "stay in place and not fall through earth"   
    Vector3D normal_body = GetKinematics().GetSupportiveFocreBody(time) - aero_and_propulsion_force_body;

    return normal_body;
}