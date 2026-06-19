#pragma once
#include "Vector3DView.h"
#include "EulerAnglesView.h"
#include "DoubleView.h"
#include <string>



struct PublishedState_6DOF {

	PublishedState_6DOF();
	double* GetLLH_ptr();
	double* GetEuler_ptr();

	std::string header_csv;
	bool termination_flag = false;

	static constexpr int NUMBER_OF_STATES = 3+3+3+3 + 3 + 3+3+3+1 + 3+3+1+1+3;
	double states[NUMBER_OF_STATES];

	// Kinematic States
	Vector3DView cg_potision_wrt_world; // meaning might change - depends on the Kinematics Type (either ECEF position or XYZ)
	Vector3DView cg_velocity_NED;
	EulerAnglesView euler_NED;
	Vector3DView rates_Body;

	Vector3DView cg_position_LLH; // In the case of Flat kinamatics - this is relative to initial position

	// Physical States
	Vector3DView CG_position_wrt_body;
	Vector3DView AeroForces;
	Vector3DView PropusiveForces;
	DoubleView mass;

	// Sensors
	Vector3DView Accelerometer;
	Vector3DView Gyro;
	DoubleView Airspeed;
	DoubleView StaticPressure;
	Vector3DView MagneticField;
};



