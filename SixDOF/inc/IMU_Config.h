#pragma once
#include "Vector3D.h" 
#include "Quaternion.h"

struct IMU_Config {
	Vector3D position_body_m; // in body frame [m] 
	Quaternion q_body_to_sensor;
};