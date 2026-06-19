#include "FlatEarthKinematics.h"
#include "IAerodynamics.h"
#include "IPropulsion.h"
#include "IGravity.h"
#include "IMassInertia.h"
#include "SixDOF.h"
#include "IPhysicalPlatform.h"
#include "IMU_Config.h"

FlatEarthKinematics::FlatEarthKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData)
	: IKinematics(sixDOF, kinematicsInitData)
{
	
}

int FlatEarthKinematics::GetStateNumber()
{
	return FlatEarthKinematics::NUM_OF_STATES;
}

void FlatEarthKinematics::SetStatesAndDerivatives(double* states, double* dStates)
{
	SetStates(states);
	ApplyStateConstraints();

	d_position_CG_XYZ.SetPtr(dStates);
	d_velocity_CG_XYZ.SetPtr(dStates + 3);
	d_q_nb.SetPtr(dStates + 6);
	d_w_nb_b.SetPtr(dStates + 10);
}

void FlatEarthKinematics::ComputeDerivatives(double time) {

	Quaternion Q_NB(q_nb);
	Vector3D W_NB_B(w_nb_b);

	// Position
	d_position_CG_XYZ = velocity_CG_XYZ;

	// Velocity
	Vector3D non_gravitational_forces_body = GetPlatform().GetNonGravitationalForcesBody(time);
	Vector3D non_gravitational_forces_NED = ImaginaryFromQuaternion(Q_NB * non_gravitational_forces_body * Q_NB.Conjugate());

	Vector3D gravity_accel_NED = GetEnviroment().Gravity().GetGravityAccelerationNED(Vector3D(position_CG_XYZ));

	double mass = GetPlatform().MassInertia().GetMass(time);

	d_velocity_CG_XYZ =
		(non_gravitational_forces_NED) / mass
		+ gravity_accel_NED;

	// Orientation
	d_q_nb = 0.5 * Q_NB * W_NB_B;

	// Rate
	Vector3D moment_wrt_cg = GetPlatform().GetMomentsAtCG(time);

	Matrix33 inertiaTensor = GetPlatform().MassInertia().GetInertiaCG(time);
	Matrix33 iinertiaTensor = GetPlatform().MassInertia().GetInertiaInverse(time);

	Vector3D engineAngularMomentum = GetPlatform().Propulsion().GetAngularMomentum();

	d_w_nb_b = iinertiaTensor *
		(moment_wrt_cg
			- Vector3D::CrossProduct(W_NB_B, inertiaTensor * W_NB_B)
			- Vector3D::CrossProduct(W_NB_B, engineAngularMomentum));
}

void FlatEarthKinematics::InitializeStates(double* states)
{
	SetStates(states);

	position_CG_XYZ = Vector3D(0, 0, 0);
	velocity_CG_XYZ = _kinematics_init.velocity_CG_wrt_NED;
	q_nb = QuaternionFromEuler(_kinematics_init.euler_CGwrtNED);
	w_nb_b = _kinematics_init.rate_CGwrtNED;

	origin_llh = Vector3D(_kinematics_init.position_llh_ddm[0] * DEG2RAD, _kinematics_init.position_llh_ddm[1] * DEG2RAD, _kinematics_init.position_llh_ddm[2]);
}

void FlatEarthKinematics::PostIntegrationUpdate(double* states)
{
	SetStates(states);
	ApplyStateConstraints();

	// normalize quaternion (numerical constraints)
	q_nb.Normalize();
}

Vector3D FlatEarthKinematics::GetSupportiveFocreBody(double time)
{

	Vector3D gravity_NED = GetEnviroment().Gravity().GetGravityAccelerationNED(Vector3D(position_CG_XYZ));

	double mass = GetPlatform().MassInertia().GetMass(time);

	Vector3D normal_NED =
		mass * (
			-gravity_NED
			);

	Quaternion Q_NB = Quaternion(q_nb);
	Vector3D normal_body = ImaginaryFromQuaternion(Q_NB.Conjugate() * normal_NED * Q_NB);

	return normal_body;
}

Quaternion FlatEarthKinematics::GetQNB()
{
	return Quaternion(q_nb);
}

Vector3D FlatEarthKinematics::GetLLH()
{
	return NavigationUtils::XYZ_to_LLH(Vector3D(position_CG_XYZ), origin_llh);
}

Vector3D FlatEarthKinematics::GetVelocityNED()
{
	return Vector3D(velocity_CG_XYZ);
}

EulerAngles FlatEarthKinematics::EulerNED2Body()
{
	return EulerFromQuaternions(Quaternion(q_nb));
}

Vector3D FlatEarthKinematics::GetWNBB()
{
	return Vector3D(w_nb_b);
}

Vector3D FlatEarthKinematics::GetAccIMU(double time)
{
	Vector3D non_gravitational_forces_body = GetPlatform().GetNonGravitationalForcesBody(time);
	double mass = GetPlatform().MassInertia().GetMass(time);
	Vector3D acc_non_grav = non_gravitational_forces_body / mass;


	// r_cg_to_sensor = - r_body_to_cg + r_body_to_sensor
	Vector3D r_cg_imu = -GetPlatform().MassInertia().CG(time) + GetPlatform().IMU_config().position_body_m;

	//// find alpha (d_w_nb_b) - like in the ComputeDerivative function
	Vector3D W_NB_B(w_nb_b);
	Vector3D moment_wrt_cg = GetPlatform().GetMomentsAtCG(time);

	Matrix33 inertiaTensor = GetPlatform().MassInertia().GetInertiaCG(time);
	Matrix33 iinertiaTensor = GetPlatform().MassInertia().GetInertiaInverse(time);

	Vector3D engineAngularMomentum = GetPlatform().Propulsion().GetAngularMomentum();

	Vector3D alpha = iinertiaTensor *
		(moment_wrt_cg
			- Vector3D::CrossProduct(W_NB_B, inertiaTensor * W_NB_B)
			- Vector3D::CrossProduct(W_NB_B, engineAngularMomentum));
	////

	// a_IMU = a_CG + alpha x r + w_IB x (w_IB x r)
	Vector3D lever_correction =
		Vector3D::CrossProduct(alpha, r_cg_imu)
		+ Vector3D::CrossProduct(W_NB_B, Vector3D::CrossProduct(W_NB_B, r_cg_imu));

	Vector3D acc_body = acc_non_grav + lever_correction;

	// Rotate into IMU sensor frame
	Quaternion q_bs = GetPlatform().IMU_config().q_body_to_sensor;
	return ImaginaryFromQuaternion(q_bs.Conjugate() * acc_body * q_bs);
}

Vector3D FlatEarthKinematics::GetWIBB()
{
	return Vector3D(w_nb_b);
}

std::string FlatEarthKinematics::GetLogHeader_12() const
{
	return "X,Y,Z,V_N,V_E,V_D,Psi,Theta,Phi,RateX,RateY,RateZ";
}

void FlatEarthKinematics::SetStates(double* states)
{
	position_CG_XYZ.SetPtr(states);
	velocity_CG_XYZ.SetPtr(states + 3);
	q_nb.SetPtr(states + 6);
	w_nb_b.SetPtr(states + 10);
}