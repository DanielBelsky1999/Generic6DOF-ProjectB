#pragma once

#include "IStatefulModel.h"
#include "IMassInertia.h"
#include "IPropulsion.h"
#include "IAerodynamics.h"
#include "IActuators.h"
#include "INormal.h"
#include "TControls.h"
#include "IMU_Config.h"


class SixDOF;
class IKinematics;
class IPhysicalModel;
class Enviroment;

class IPhysicalPlatform
{
	friend class IKinematics;
	friend class IPhysicalModel;
	friend class SixDOF;

public:

	virtual ~IPhysicalPlatform();

	// to be called by SixDOF - todo move to private?
	void SetSixDOF(SixDOF* sixDOF);
	int GetTotalStateNumber();
	void BindStateVectors(double* new_states, double* new_dStates);
	void ComputeDerivatives(double time);
	void InitializeStates(double* states);
	void PostIntegrationUpdate(double* states);

	// called by Kinematics
	Vector3D GetNonGravitationalForcesBody(double time);
	Vector3D GetMomentsAtCG(double time);
	
	// Used across models and also by kinematics - should be private with accessors todo
	IMassInertia& MassInertia();
	IPropulsion& Propulsion();
	IAerodynamics& Aerodynamics();
	IActuators& Actuators();
	IMU_Config& IMU_config();

protected:
	// Accessors (intended to be used by IPhysicalModel who is a friend)
	Enviroment& GetEnvoriment();
	IKinematics& GetKinematics();
	TControls& Controls();

	// Inhereting classes will call these.
	void SetModels(IMassInertia* mass_inertia,IPropulsion* propulsion,IAerodynamics* aerodynamics, IActuators* actuators, INormal* normal, TControls* controls);
	void AssignModelsToStatefulModelArray(IStatefulModel* mass_inertia, IStatefulModel* propulsion, IStatefulModel* aerodynamics, IStatefulModel* actuators, IStatefulModel* normal);
	void SetIMUConfig(Vector3D position, Quaternion q_body_sensor);

	// TControls
	TControls* _tcontrols;

private:
	static constexpr int NUM_OF_MODELS = 5;
	IStatefulModel* _models_array[NUM_OF_MODELS]; // Use to iterate the models w.o. using std::vector and Iterator
	// Stateful/Stateless models - that need to inherit from IPhysicalModel (to be able to call each-others' function)
	IMassInertia* _mass_inertia;
	IPropulsion* _propulsion;
	IAerodynamics* _aerodynamics;
	IActuators* _actuators;
	INormal* _normal;

	IMU_Config _imu_config;

	// six dof pointer - to get the kinematics and Environment from there
	SixDOF* _sixDOF;

};

