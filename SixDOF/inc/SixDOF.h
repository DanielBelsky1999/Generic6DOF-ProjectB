#pragma once

#include "IntegratorFactory.h"
#include "KinematicsFactory.h"

#include "Enviroment.h"
#include "IPhysicalPlatform.h"

#include "PublishedState.h"

class SixDOF {

	friend class IPhysicalPlatform;
	friend class Integrator;
	friend class IKinematics;

public:

	void Init(Enviroment* enviroment, IPhysicalPlatform* physicalPlatform, KinematicsInitData kinematicsInitData, PublishedState_6DOF* published_state);
	void Step(double time);

	void PrintState();

	~SixDOF();

private:
	IKinematics* _kinematics;
	Enviroment* _enviroment;
	IPhysicalPlatform* _physicalPlatform;
	Integrator* _integrator;

	void BindStateVectors(double* new_states, double* new_dStates);
	void ComputeDerivatives(double time);
	void PostIntegrationUpdate();
	void PublishStates(double time);

	int _stateCounter = 0;
	double* _state_vector = nullptr;

	PublishedState_6DOF* _published_state;
};