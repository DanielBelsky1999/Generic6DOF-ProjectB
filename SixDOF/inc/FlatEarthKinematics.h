#pragma once
#include "IKinematics.h"
#include "Vector3DView.h"
#include "QuaternionView.h"
#include "LinearAlgebraOps.h"
#include "nav_math_operators.h"

class FlatEarthKinematics : public IKinematics
{
public:
	FlatEarthKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData);

	int GetStateNumber() override;

	void SetStatesAndDerivatives(double* states, double* dStates) override;
	void ComputeDerivatives(double time) override;

	void InitializeStates(double* states) override;
	void PostIntegrationUpdate(double* states) override;

	// Interface for other Models - todo I want this to implement IKinematics
	Vector3D GetPosition() override { return Vector3D(position_CG_XYZ); }
	double GetAltitude() override { return -position_CG_XYZ[2]; }
	// To be used by normal models
	Vector3D GetSupportiveFocreBody(double time) override;
	Quaternion GetQNB() override;

	// for publishing and models
	Vector3D GetLLH() override;
	Vector3D GetVelocityNED() override;
	EulerAngles EulerNED2Body() override;
	Vector3D GetWNBB() override;

	// for the IMU model
	Vector3D GetAccIMU(double time) override;
	Vector3D GetWIBB() override;

	std::string GetLogHeader_12() const override;

private:
	static constexpr int NUM_OF_STATES = 13;

	Vector3DView position_CG_XYZ;
	Vector3DView velocity_CG_XYZ;
	QuaternionView q_nb; // V_body = q_nb* x v_NED x q_nb
	Vector3DView w_nb_b; // Angular velocity of body w.r.t. inertial, expressed in body frame

	Vector3DView d_position_CG_XYZ;
	Vector3DView d_velocity_CG_XYZ;
	QuaternionView d_q_nb;
	Vector3DView d_w_nb_b;

	void SetStates(double* states) override;

	// Specific only for this kind of Kinematics
	Vector3D origin_llh;
};

