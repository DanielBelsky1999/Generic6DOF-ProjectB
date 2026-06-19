#include "Integrator.h"
#include "SixDOF.h"


Integrator::Integrator(SixDOF* sixDOF, double DT)
	:_sixDOF(sixDOF), _DT(DT)
{
}

void Integrator::CallBindStateVectors(double* new_states, double* new_dStates)
{
	_sixDOF->BindStateVectors(new_states, new_dStates);
}

double* Integrator::GetSixDOFsStateVector()
{
	return _sixDOF->_state_vector;
}

void Integrator::CallComputeDerivatives(double time)
{
	_sixDOF->ComputeDerivatives(time);
}

