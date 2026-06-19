#include "IAerodynamics.h"
#include "IKinematics.h"


IAerodynamics::IAerodynamics(IPhysicalPlatform* platform)
	: IPhysicalModel(platform)
{
}

double IAerodynamics::GetAOA()
{
	Vector3D vel_Body = GetVelocityBody();

	if (abs(vel_Body[0]) < D_EPS) return 0;
	return atan(vel_Body[2] / vel_Body[0]);
}

double IAerodynamics::GetBeta()
{
	Vector3D vel_Body = GetVelocityBody();

	double V = vel_Body.Norm();
	if (abs(V) < D_EPS) return 0;
	return asin(vel_Body[1] / V);
}

Vector3D IAerodynamics::GetVelocityBody() {
	Vector3D vel_NED = GetKinematics().GetVelocityNED();
	Quaternion q_nb = GetKinematics().GetQNB();

	return ImaginaryFromQuaternion(q_nb.Conjugate() * vel_NED * q_nb);
}
