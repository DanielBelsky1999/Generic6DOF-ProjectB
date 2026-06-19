#include "IPhysicalModel.h"
#include "IPhysicalPlatform.h"

IPhysicalModel::IPhysicalModel(IPhysicalPlatform* platform) 
	: _platform(platform)
{

}

IMassInertia& IPhysicalModel::GetMassInertia()
{
	return _platform->MassInertia();
}

IPropulsion& IPhysicalModel::GetPropulsion()
{
	return _platform->Propulsion();
}

IAerodynamics& IPhysicalModel::GetAerodynamics()
{
	return _platform->Aerodynamics();
}

IActuators& IPhysicalModel::GetActuators()
{
	return _platform->Actuators();
}

IKinematics& IPhysicalModel::GetKinematics()
{
	return _platform->GetKinematics();
}

Enviroment& IPhysicalModel::GetEnviroment()
{
	return _platform->GetEnvoriment();
}

TControls& IPhysicalModel::GetControls()
{
	return _platform->Controls();
}
