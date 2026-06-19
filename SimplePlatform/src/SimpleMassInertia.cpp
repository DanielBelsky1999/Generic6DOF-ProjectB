#include "SimpleMassInertia.h"
#include "IPropulsion.h"

SimpleMassInertia::SimpleMassInertia(IPhysicalPlatform* platform)
	: IMassInertia(platform)
{

}

double SimpleMassInertia::GetMass(double time) const
{
	return double(mass);
}

Matrix33 SimpleMassInertia::GetInertiaCG(double time) const
{
	return Matrix33(1,0,0,0,1,0,0,0,1);
}

Matrix33 SimpleMassInertia::GetInertiaInverse(double time) const
{
	return Matrix33(1,0,0,0,1,0,0,0,1);
}

Vector3D SimpleMassInertia::CG(double time) const
{
	return Vector3D(1,0,0);
}

int SimpleMassInertia::GetStateNumber()
{
	return NUM_OF_STATES;
}

void SimpleMassInertia::SetStatesAndDerivatives(double* states, double* dStates)
{
	SetStates(states);
	ApplyStateConstraints();

	dmass.SetPtr(dStates);
}

void SimpleMassInertia::ComputeDerivatives(double time)
{
	dmass = -GetPropulsion().GetMassFlowRate(time);
}

void SimpleMassInertia::InitializeStates(double* states)
{
	SetStates(states);
	mass = 7;
}

void SimpleMassInertia::PostIntegrationUpdate(double* states)
{
	SetStates(states);
	ApplyStateConstraints();
}

void SimpleMassInertia::SetStates(double* states)
{
	mass.SetPtr(states);
}

