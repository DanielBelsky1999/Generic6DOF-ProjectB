#include "SixDOF.h"


void SixDOF::Init(Enviroment* enviroment, IPhysicalPlatform* physicalPlatform, KinematicsInitData kinematicsInitData, PublishedState_6DOF* published_state)
{
	_enviroment = enviroment;
	_physicalPlatform = physicalPlatform;

	_physicalPlatform->SetSixDOF(this);
	_kinematics = KinematicsFactory::CreateKinematics(this, kinematicsInitData);

	// count total states
	_stateCounter += _kinematics->GetStateNumber();
	_stateCounter += _physicalPlatform->GetTotalStateNumber();

	// allocate array just the needed size
	_state_vector = new double[_stateCounter];

	// initialize integrator
	_integrator = IntegratorFactory::CreateIntegrator(this);
	_integrator->Init(_stateCounter);

	// Call Inits:
	_kinematics->InitializeStates(_state_vector);
	int stateCounterOffset = _kinematics->GetStateNumber();
	_physicalPlatform->InitializeStates(&_state_vector[stateCounterOffset]);

	_published_state = published_state;
	_published_state->header_csv = _kinematics->GetLogHeader_12() + "," + "Lat,Long,Alt,CGbx,CGby,CGbz,Aerox,Aeroy,Aeroz,Propx,Propy,Propz,Mass,Accx,Accy,Accz,GyroX,GyroY,GyroZ,Aspd,SPress,MagX,MagY,MagZ";
	PublishStates(0);	// Assumes simulation starts at time = 0. todo - get from outside 
						// Also assumes someone, like a flight computer, will need the published states before the first Step() is called.
}

SixDOF::~SixDOF()
{
	delete _kinematics;
	delete _integrator;
	delete[] _state_vector;
}

void SixDOF::Step(double time) {
	PublishStates(time);
	_integrator->Step(time);
	PostIntegrationUpdate();
}

void SixDOF::BindStateVectors(double* new_states, double* new_dStates)
{
	_kinematics->SetStatesAndDerivatives(new_states, new_dStates);
	int stateCounterOffset = _kinematics->GetStateNumber();
	_physicalPlatform->BindStateVectors(&new_states[stateCounterOffset], &new_dStates[stateCounterOffset]);
}

void SixDOF::ComputeDerivatives(double time)
{
	_kinematics->ComputeDerivatives(time);
	_physicalPlatform->ComputeDerivatives(time);
}

void SixDOF::PostIntegrationUpdate()
{
	_kinematics->PostIntegrationUpdate(_state_vector);
	int stateCounterOffset = _kinematics->GetStateNumber();
	_physicalPlatform->PostIntegrationUpdate(&_state_vector[stateCounterOffset]);
}

void SixDOF::PublishStates(double time)
{
	_published_state->cg_potision_wrt_world = _kinematics->GetPosition();
	_published_state->cg_velocity_NED = _kinematics->GetVelocityNED();
	_published_state->euler_NED = _kinematics->EulerNED2Body();
	_published_state->rates_Body = _kinematics->GetWNBB();

	_published_state->cg_position_LLH = _kinematics->GetLLH();
	
	_published_state->CG_position_wrt_body = _physicalPlatform->MassInertia().CG(time);
	_published_state->AeroForces = _physicalPlatform->Aerodynamics().GetAeroForceBody();
	_published_state->PropusiveForces = _physicalPlatform->Propulsion().GetPropulsiveForceBody(time);
	_published_state->mass = _physicalPlatform->MassInertia().GetMass(time);

	_published_state->Accelerometer = _kinematics->GetAccIMU(time);
	_published_state->Gyro = _kinematics->GetWIBB();
	_published_state->Airspeed = _physicalPlatform->Aerodynamics().GetVelocityBody().Norm();
	_published_state->StaticPressure = _enviroment->Atmosphere().GetPressure(_kinematics->GetAltitude());
	_published_state->MagneticField = _enviroment->MagneticField().GetMagneticField_sensor(_kinematics->GetLLH(), QuaternionFromEuler(_kinematics->EulerNED2Body())*_physicalPlatform->IMU_config().q_body_to_sensor);

	// Determines wether the simulation should be stoped
	_published_state->termination_flag = (_kinematics->GetAltitude() < -D_EPS);
}

// todo remove
#include <iostream>
#include <iomanip>
void SixDOF::PrintState() {
	for (int i = 0; i < _stateCounter; i++) {
		std::cout << std::setprecision(15) << _state_vector[i] << "\n";
	}
}
