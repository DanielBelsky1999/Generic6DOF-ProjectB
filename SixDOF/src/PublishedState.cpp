#include "PublishedState.h"

PublishedState_6DOF::PublishedState_6DOF()
{
	// Kinematic States
	cg_potision_wrt_world.SetPtr(states);
	cg_velocity_NED.SetPtr(states+3);
	euler_NED.SetPtr(states+6);
	rates_Body.SetPtr(states+9);

	// LLH position
	cg_position_LLH.SetPtr(states + 12);

	// Some models' states
	CG_position_wrt_body.SetPtr(states+15);
	AeroForces.SetPtr(states+18);
	PropusiveForces.SetPtr(states+21);
	mass.SetPtr(states + 24);

	// Sensors
	Accelerometer.SetPtr(states+25);
	Gyro.SetPtr(states+28);
	Airspeed.SetPtr(states+31);
	StaticPressure.SetPtr(states+32);
	MagneticField.SetPtr(states+33);
}

double* PublishedState_6DOF::GetLLH_ptr() {
	return states + 12;
};
double* PublishedState_6DOF::GetEuler_ptr() {
	return states + 6;
};