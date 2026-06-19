#include "SimpleActuators.h"
#include "SimplePlatformControls.h"

SimpleActuators::SimpleActuators(IPhysicalPlatform* platform)
	: IActuators(platform)
{

}

double SimpleActuators::GetActuator(int indx)
{
	return double(fin_angle[indx]);
}

int SimpleActuators::GetStateNumber()
{
	return NUM_OF_STATES;
}

void SimpleActuators::SetStatesAndDerivatives(double* states, double* dStates)
{
	SetStates(states);
	ApplyStateConstraints();

	for (int i = 0; i < 4; i++)
	{
		d_fin_angle[i].SetPtr(&dStates[i]);
	}
}

#include <iomanip>
#include <iostream>
void SimpleActuators::ComputeDerivatives(double time)
{
	SimplePlatformControls& controls = static_cast<SimplePlatformControls&>(GetControls());
	for (int i = 0; i < 4; i++)
	{
		d_fin_angle[i] = controls.fins[i] - double(fin_angle[i]);
	}
}

void SimpleActuators::InitializeStates(double* states)
{
	SetStates(states);
	for (int i = 0; i < 4; i++)
	{
		fin_angle[i] = 0;
	}
}

void SimpleActuators::PostIntegrationUpdate(double* states)
{
	SetStates(states);
	ApplyStateConstraints();
}

void SimpleActuators::SetStates(double* states)
{
	for (int i = 0; i < 4; i++)
	{
		fin_angle[i].SetPtr(&states[i]);
	}
}
