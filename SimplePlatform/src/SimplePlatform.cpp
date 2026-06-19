#include "SimplePlatform.h"

SimplePlatform::SimplePlatform(TControls* controls)
{
	sMassInertia = new SimpleMassInertia(this);
	sPropulsion = new SimplePropulsion(this);
	sAerodynamics = new SimpleAerodynamics(this);
	sActuators = new SimpleActuators(this);
	sNormal = new SimpleNormal(this);
	// deletes are handled in IPhysicalPlatform's destructor. 
	// Later will be std::moved() into the IPhysicalPlatform todo


	// MUST-CALL functions! 
	// todo find a way of doing this from within the IPhysicalPlatform and not to require it
	SetModels(sMassInertia, sPropulsion, sAerodynamics, sActuators, sNormal, controls);
	AssignModelsToStatefulModelArray(sMassInertia, sPropulsion, sAerodynamics, sActuators, sNormal);

	// MUST-DO: Configure IMU position
	Vector3D imu_position = Vector3D(1, 0, 0); // In this example, the imu is at C.G. (as written in SimpleMassInertia)
	Quaternion imu_orientation = Quaternion(); // Unit quternion. IMU orientation the same as body attitude
	// MUST-CALL function!
	SetIMUConfig(imu_position, imu_orientation);
}



