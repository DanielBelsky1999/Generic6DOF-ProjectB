#include "IKinematics.h"
#include "SixDOF.h"

IKinematics::IKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData) : _sixDOF(sixDOF), _kinematics_init(kinematicsInitData)
{
}

IPhysicalPlatform& IKinematics::GetPlatform()
{
	return *_sixDOF->_physicalPlatform;
}

Enviroment& IKinematics::GetEnviroment()
{
	return *_sixDOF->_enviroment;
}
