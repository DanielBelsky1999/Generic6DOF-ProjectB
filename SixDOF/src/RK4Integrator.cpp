#include "RK4Integrator.h"


RK4Integrator::RK4Integrator(SixDOF* sixDOF, double DT)
	:Integrator(sixDOF, DT)
{
}

void RK4Integrator::Init(int numStates)
{
	_numStates = numStates;
	k1 = new double[numStates];
	k2 = new double[numStates];
	k3 = new double[numStates];
	k4 = new double[numStates];
	_states1 = new double[numStates];
	_states2 = new double[numStates];
	_states3 = new double[numStates];
}

RK4Integrator::~RK4Integrator()
{
	delete[] k1;
	delete[] k2;
	delete[] k3;
	delete[] k4;
	delete[] _states1;
	delete[] _states2;
	delete[] _states3;
}

void RK4Integrator::Step(double time)
{
	double* sixdof_state_vector = Integrator::GetSixDOFsStateVector();

	Integrator::CallBindStateVectors(sixdof_state_vector, k1);
	Integrator::CallComputeDerivatives(time);

	for (int i = 0; i < _numStates; i++) {
		_states1[i] = sixdof_state_vector[i] + k1[i] * (_DT / 2);
	}
	Integrator::CallBindStateVectors(_states1, k2);
	Integrator::CallComputeDerivatives(time + (_DT / 2));

	for (int i = 0; i < _numStates; i++) {
		_states2[i] = sixdof_state_vector[i] + k2[i] * (_DT / 2);
	}
	Integrator::CallBindStateVectors(_states2, k3);
	Integrator::CallComputeDerivatives(time + (_DT / 2));

	for (int i = 0; i < _numStates; i++) {
		_states3[i] = sixdof_state_vector[i] + k3[i] * _DT;
	}
	Integrator::CallBindStateVectors(_states3, k4);
	Integrator::CallComputeDerivatives(time + (_DT));


	// operating directly on SixDOF's state vector
	for (int i = 0; i < _numStates; i++) {
		sixdof_state_vector[i] += (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]) * (_DT / 6.0);
	}
}