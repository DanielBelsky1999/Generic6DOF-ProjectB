#pragma once

class IStatefulModel
{
public:

	virtual int GetStateNumber() = 0;

	// To be used by the integrator
	virtual void SetStatesAndDerivatives(double* states, double* dStates) = 0;
	virtual void ComputeDerivatives(double time) = 0;

	// To be called by SixDOF
	virtual void InitializeStates(double* states) = 0;
	virtual void PostIntegrationUpdate(double* states) = 0;

	virtual ~IStatefulModel() = default;

protected:
	virtual void SetStates(double* states) = 0;
	virtual void ApplyStateConstraints() {};

};

