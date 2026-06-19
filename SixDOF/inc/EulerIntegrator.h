#pragma once
#include "Integrator.h"

class EulerIntegrator : public Integrator
{
public:
	EulerIntegrator(SixDOF* sixDOF, double DT);

	void Init(int numStates) override;
	void Step(double time) override;

	~EulerIntegrator();

private:
	double* _dStates = nullptr;
};

