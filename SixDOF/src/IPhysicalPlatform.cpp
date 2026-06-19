#include "IPhysicalPlatform.h"
#include "IStatefulModel.h"
#include "SixDOF.h"

IPhysicalPlatform::~IPhysicalPlatform() {
	delete _mass_inertia;
	delete _aerodynamics;
	delete _propulsion;
	delete _actuators;
	delete _normal;
}

void IPhysicalPlatform::SetSixDOF(SixDOF* sixDOF) {
	_sixDOF = sixDOF;
}

int IPhysicalPlatform::GetTotalStateNumber()
{
	int numOfStates = 0;
	for (int i = 0; i < NUM_OF_MODELS; i++) {
		numOfStates += _models_array[i]->GetStateNumber();
	}
	return numOfStates;
}

void IPhysicalPlatform::BindStateVectors(double* new_states, double* new_dStates)
{
	int stateCounterOffset = 0;
	for (int i = 0; i < NUM_OF_MODELS; i++) {
		_models_array[i]->SetStatesAndDerivatives(&new_states[stateCounterOffset], &new_dStates[stateCounterOffset]);
		stateCounterOffset += _models_array[i]->GetStateNumber();
	}
}

void IPhysicalPlatform::ComputeDerivatives(double time)
{
	for (int i = 0; i < NUM_OF_MODELS; i++) {
		_models_array[i]->ComputeDerivatives(time);
	}
}

void IPhysicalPlatform::PostIntegrationUpdate(double* states)
{
	int stateCounterOffset = 0;
	for (int i = 0; i < NUM_OF_MODELS; i++) {
		_models_array[i]->PostIntegrationUpdate(&states[stateCounterOffset]);
		stateCounterOffset += _models_array[i]->GetStateNumber();
	}
}

void IPhysicalPlatform::InitializeStates(double* states)
{
	int stateCounterOffset = 0;
	for (int i = 0; i < NUM_OF_MODELS; i++) {
		_models_array[i]->InitializeStates(&states[stateCounterOffset]);
		stateCounterOffset += _models_array[i]->GetStateNumber(); 
	}
}

Enviroment& IPhysicalPlatform::GetEnvoriment() 
{
	return *_sixDOF->_enviroment;
}

Vector3D IPhysicalPlatform::GetNonGravitationalForcesBody(double time)
{
	return _aerodynamics->GetAeroForceBody() + _propulsion->GetPropulsiveForceBody(time) + _normal->GetNormalBody(time);
}

IKinematics& IPhysicalPlatform::GetKinematics()
{
	return *_sixDOF->_kinematics;
}

Vector3D IPhysicalPlatform::GetMomentsAtCG(double time)
{
	return _aerodynamics->GetAeroMomentAtCG() + _propulsion->GetPropulsiveMomentAtCG(time);
}

IMassInertia& IPhysicalPlatform::MassInertia()
{
	return *_mass_inertia;
}

IPropulsion& IPhysicalPlatform::Propulsion()
{
	return *_propulsion;
}

IAerodynamics& IPhysicalPlatform::Aerodynamics()
{
	return *_aerodynamics;
};

IActuators& IPhysicalPlatform::Actuators() {
	return *_actuators;
};

TControls& IPhysicalPlatform::Controls() {
	return *_tcontrols;
}
IMU_Config& IPhysicalPlatform::IMU_config()
{
	return _imu_config;
};


void IPhysicalPlatform::SetModels(IMassInertia* mass_inertia, IPropulsion* propulsion, IAerodynamics* aerodynamics, IActuators* actuators, INormal* normal, TControls* controls) {
	_mass_inertia = mass_inertia;
	_propulsion = propulsion;
	_aerodynamics = aerodynamics;
	_actuators = actuators;
	_normal = normal;
	_tcontrols = controls;
};

void IPhysicalPlatform::AssignModelsToStatefulModelArray(IStatefulModel* mass_inertia, IStatefulModel* propulsion, IStatefulModel* aerodynamics, IStatefulModel* actuators, IStatefulModel* normal) {
	_models_array[0] = mass_inertia;
	_models_array[1] = propulsion;
	_models_array[2] = aerodynamics;
	_models_array[3] = actuators;
	_models_array[4] = normal;
};

void IPhysicalPlatform::SetIMUConfig(Vector3D position, Quaternion q_body_sensor) {
	_imu_config.position_body_m = position;
	_imu_config.q_body_to_sensor = q_body_sensor;
}