#pragma once
#include "IKinematics.h"
#include "Vector3DView.h"
#include "QuaternionView.h"
#include "LinearAlgebraOps.h"
#include "nav_math_operators.h"
#include "NavigationUtils.h"

class ECEFKinematics : public IKinematics
{
public:
	ECEFKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData);

	int GetStateNumber() override;

	void SetStatesAndDerivatives(double* states, double* dStates) override;
	void ComputeDerivatives(double time) override;

	void InitializeStates(double* states) override;
	void PostIntegrationUpdate(double* states) override;

	// Interface for other Models - todo I want this to implement IKinematics
	Vector3D GetPosition() override { return Vector3D(position_CG_ECEF); }
	double GetAltitude() override { return GetLLH()[2]; }
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

	Vector3DView position_CG_ECEF;
	Vector3DView velocity_CG_ECEF;
	QuaternionView q_eb; // V_body = q_eb* x v_ecef x q_eb
	Vector3DView w_ib_b; // Angular velocity of body w.r.t. inertial, expressed in body frame

	Vector3DView d_position_CG_ECEF;
	Vector3DView d_velocity_CG_ECEF;
	QuaternionView d_q_eb;
	Vector3DView d_w_ib_b;

	void SetStates(double* states) override;

	// Specific only for this kind of Kinematics
	Vector3D W_IE_E;
};