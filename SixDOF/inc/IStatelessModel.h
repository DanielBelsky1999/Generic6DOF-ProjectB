#pragma once

#include "IStatefulModel.h"

class IStatelessModel : public IStatefulModel 
{
public:

	int GetStateNumber() override final { return 0; };
	void SetStatesAndDerivatives(double* states, double* dStates) override final {};
	void ComputeDerivatives(double time) override final {};
	void InitializeStates(double* states) override final {};
	void PostIntegrationUpdate(double* states) override final {};

protected:
	void SetStates(double* states) override final {};
	void ApplyStateConstraints() override final {};
};