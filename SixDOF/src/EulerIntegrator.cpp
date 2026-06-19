#include "EulerIntegrator.h"

EulerIntegrator::EulerIntegrator(SixDOF* sixDOF, double DT)
	:Integrator(sixDOF,DT)
{
}

void EulerIntegrator::Init(int numStates)
{
	_numStates = numStates;
	_dStates = new double[numStates];

	// bind the state and state-derivative vector, since they are not expected to change during Euler integration
	Integrator::CallBindStateVectors(Integrator::GetSixDOFsStateVector(), _dStates);
}

EulerIntegrator::~EulerIntegrator()
{
	delete[] _dStates;
}

void EulerIntegrator::Step(double time)
{
	Integrator::CallComputeDerivatives(time);
	double* sixdof_state_vector = Integrator::GetSixDOFsStateVector();
	// operating directly on SixDOF's state vector with no intermediate state-vectors.
	for (int i = 0; i < _numStates; i++) {
		sixdof_state_vector[i] += _dStates[i] * _DT;
	}

}

