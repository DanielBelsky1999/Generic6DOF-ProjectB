#include "ECEFKinematics.h"
#include "IAerodynamics.h"
#include "IPropulsion.h"
#include "IGravity.h"
#include "IMassInertia.h"
#include "SixDOF.h"
#include "IPhysicalPlatform.h"

ECEFKinematics::ECEFKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData) 
    : IKinematics(sixDOF, kinematicsInitData)
{
	// set W_IE_E
	if (Initializer::GetValueAsBool("World/Earth/Ellipsoid/IsRotating")) {
		W_IE_E = Vector3D(0, 0, 7.292115e-5);
	}
	else {
		W_IE_E = Vector3D(0, 0, 0);
	}
}

int ECEFKinematics::GetStateNumber()
{
	return ECEFKinematics::NUM_OF_STATES;
}

void ECEFKinematics::SetStatesAndDerivatives(double* states, double* dStates)
{
	SetStates(states);
	ApplyStateConstraints();

	d_position_CG_ECEF.SetPtr(dStates);
	d_velocity_CG_ECEF.SetPtr(dStates + 3);
	d_q_eb.SetPtr(dStates + 6);
	d_w_ib_b.SetPtr(dStates + 10);
}

void ECEFKinematics::ComputeDerivatives(double time) {

	Quaternion Q_EB(q_eb);
	Vector3D W_IB_B(w_ib_b);

	// Position
	d_position_CG_ECEF = velocity_CG_ECEF;

	// Velocity
	Vector3D non_gravitational_forces_body = GetPlatform().GetNonGravitationalForcesBody(time);
	Vector3D non_gravitational_forces_ecef = ImaginaryFromQuaternion(Q_EB * non_gravitational_forces_body * Q_EB.Conjugate());

	Vector3D gravity_accel_NED = GetEnviroment().Gravity().GetGravityAccelerationNED(Vector3D(position_CG_ECEF));
	Vector3D llh = GetLLH();
	Quaternion q_en = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
	Vector3D gravity_accel_ecef = ImaginaryFromQuaternion(q_en * gravity_accel_NED * q_en.Conjugate());

	double mass = GetPlatform().MassInertia().GetMass(time);

	d_velocity_CG_ECEF =
		(non_gravitational_forces_ecef) / mass
		+ gravity_accel_ecef
		- 2.0 * Vector3D::CrossProduct(W_IE_E, Vector3D(velocity_CG_ECEF))
		- Vector3D::CrossProduct(W_IE_E, Vector3D::CrossProduct(W_IE_E, Vector3D(position_CG_ECEF)));

	// Orientation
	Vector3D W_IE_B = ImaginaryFromQuaternion(Q_EB.Conjugate() * W_IE_E * Q_EB);
	Vector3D W_EB_B = (W_IB_B - W_IE_B);
	d_q_eb = 0.5 * Q_EB * W_EB_B;

	// Rate
	Vector3D moment_wrt_cg = GetPlatform().GetMomentsAtCG(time);

	Matrix33 inertiaTensor = GetPlatform().MassInertia().GetInertiaCG(time);
	Matrix33 iinertiaTensor = GetPlatform().MassInertia().GetInertiaInverse(time);
 
	Vector3D engineAngularMomentum = GetPlatform().Propulsion().GetAngularMomentum();

	d_w_ib_b = iinertiaTensor *
		(moment_wrt_cg
		- Vector3D::CrossProduct(W_IB_B, inertiaTensor * W_IB_B)
		- Vector3D::CrossProduct(W_IB_B, engineAngularMomentum));

}

void ECEFKinematics::InitializeStates(double* states)
{
	SetStates(states);

	position_CG_ECEF = NavigationUtils::LLH_to_ECEF(_kinematics_init.position_llh_ddm);
	velocity_CG_ECEF = NavigationUtils::BodyVelwrtNED_to_ECEF(_kinematics_init.euler_CGwrtNED, _kinematics_init.position_llh_ddm, _kinematics_init.velocity_CG_wrt_NED);
	q_eb = NavigationUtils::EulerwrtNED_to_qeb(_kinematics_init.euler_CGwrtNED, _kinematics_init.position_llh_ddm);
	w_ib_b = NavigationUtils::W_NB_B_to_W_IB_B(W_IE_E, _kinematics_init.rate_CGwrtNED, _kinematics_init.euler_CGwrtNED, _kinematics_init.position_llh_ddm, _kinematics_init.velocity_CG_wrt_NED);
}

void ECEFKinematics::PostIntegrationUpdate(double* states)
{
	SetStates(states);
	ApplyStateConstraints();

	// normalize quaternion (numerical constraints)
	q_eb.Normalize();
}

Vector3D ECEFKinematics::GetSupportiveFocreBody(double time)
{

	Vector3D position_ecef = Vector3D(position_CG_ECEF);

	Vector3D gravity_NED = GetEnviroment().Gravity().GetGravityAccelerationNED(position_ecef);

	Vector3D llh = GetLLH();
	Quaternion q_en = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));

	Vector3D gravity_ecef = ImaginaryFromQuaternion(q_en * gravity_NED * q_en.Conjugate());

	double mass = GetPlatform().MassInertia().GetMass(time);

	Vector3D normal_ecef =
		mass * (
			-gravity_ecef
			// Assume stationary target....
			/*+ 2.0 * Vector3D::CrossProduct(NavigationUtils::W_IE_E, Vector3D(velocity_CG_ECEF))*/
			+ Vector3D::CrossProduct(W_IE_E, Vector3D::CrossProduct(W_IE_E, position_ecef)));
	
	Quaternion Q_EB = Quaternion(q_eb);
	Vector3D normal_body = ImaginaryFromQuaternion(Q_EB.Conjugate() * normal_ecef * Q_EB);

	return normal_body;
}

Quaternion ECEFKinematics::GetQNB()
{
	Quaternion Q_EB(q_eb);

	Vector3D llh = GetLLH();

	Quaternion qen = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));
	Quaternion qnb = qen.Conjugate() * Q_EB;
	return qnb;
}

Vector3D ECEFKinematics::GetLLH()
{
	return NavigationUtils::ECEF_to_LLH(Vector3D(position_CG_ECEF));
}

Vector3D ECEFKinematics::GetVelocityNED()
{
	return NavigationUtils::ECEF_to_NED(Vector3D(velocity_CG_ECEF), Vector3D(position_CG_ECEF));
}

EulerAngles ECEFKinematics::EulerNED2Body()
{
	return NavigationUtils::qeb_to_EulerwrtNED(Quaternion(q_eb), Vector3D(position_CG_ECEF));
}

Vector3D ECEFKinematics::GetWNBB()
{
	Quaternion Q_EB(q_eb);
	Vector3D VelCGwrtNED_body = ImaginaryFromQuaternion(Q_EB.Conjugate() * Vector3D(velocity_CG_ECEF) * Q_EB);
	return NavigationUtils::W_IB_B_to_W_NB_B(W_IE_E, Vector3D(w_ib_b), EulerNED2Body(), GetLLH(), VelCGwrtNED_body);
}

Vector3D ECEFKinematics::GetAccIMU(double time)
{
	Vector3D non_gravitational_forces_body = GetPlatform().GetNonGravitationalForcesBody(time);
	double mass = GetPlatform().MassInertia().GetMass(time);
	Vector3D acc_non_grav = non_gravitational_forces_body / mass;


	// r_cg_to_sensor = - r_body_to_cg + r_body_to_sensor
	Vector3D r_cg_imu = -GetPlatform().MassInertia().CG(time) + GetPlatform().IMU_config().position_body_m;

	//// find alpha (d_w_ib_b) - like in the ComputeDerivative function
	Vector3D W_IB_B(w_ib_b);
	Vector3D moment_wrt_cg = GetPlatform().GetMomentsAtCG(time);

	Matrix33 inertiaTensor = GetPlatform().MassInertia().GetInertiaCG(time);
	Matrix33 iinertiaTensor = GetPlatform().MassInertia().GetInertiaInverse(time);

	Vector3D engineAngularMomentum = GetPlatform().Propulsion().GetAngularMomentum();

	Vector3D alpha = iinertiaTensor *
		(moment_wrt_cg
			- Vector3D::CrossProduct(W_IB_B, inertiaTensor * W_IB_B)
			- Vector3D::CrossProduct(W_IB_B, engineAngularMomentum));
	////

	// a_IMU = a_CG + alpha x r + w_IB x (w_IB x r)
	Vector3D lever_correction =
		Vector3D::CrossProduct(alpha, r_cg_imu)
		+ Vector3D::CrossProduct(W_IB_B, Vector3D::CrossProduct(W_IB_B, r_cg_imu));

	Vector3D acc_body = acc_non_grav + lever_correction;

	// Rotate into IMU sensor frame
	Quaternion q_bs = GetPlatform().IMU_config().q_body_to_sensor;
	return ImaginaryFromQuaternion(q_bs.Conjugate() * acc_body * q_bs);
}

Vector3D ECEFKinematics::GetWIBB()
{
	return Vector3D(w_ib_b);
}

std::string ECEFKinematics::GetLogHeader_12() const
{
	return "X_ECEF,Y_ECEF,Z_ECEF,V_N,V_E,V_D,Psi,Theta,Phi,RateX,RateY,RateZ";
}

void ECEFKinematics::SetStates(double* states)
{
	position_CG_ECEF.SetPtr(states);
	velocity_CG_ECEF.SetPtr(states + 3);
	q_eb.SetPtr(states + 6);
	w_ib_b.SetPtr(states + 10);
}