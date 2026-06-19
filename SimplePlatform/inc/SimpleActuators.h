#pragma once
#include "IActuators.h"
#include "IStatefulModel.h"
#include "DoubleView.h"

class SimpleActuators : public IActuators, public IStatefulModel
{
public:
	SimpleActuators(IPhysicalPlatform* platform);

	// Inherited via IActuator
	double GetActuator(int indx) override;

	// Inherited via IStatefulModel
	int GetStateNumber() override;

	void SetStatesAndDerivatives(double* states, double* dStates) override;
	void ComputeDerivatives(double time) override;

	void InitializeStates(double* states) override;
	void PostIntegrationUpdate(double* states) override;

private:
	void SetStates(double* states) override;

private:
	static constexpr int NUM_OF_STATES = 4;

	// states
	DoubleView fin_angle[4];
	// state derivatives
	DoubleView d_fin_angle[4];
};

