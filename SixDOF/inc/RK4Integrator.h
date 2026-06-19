#pragma once
#include "Integrator.h"

class RK4Integrator : public Integrator
{
public:
	RK4Integrator(SixDOF* sixDOF, double DT);

	void Init(int numStates) override;
	void Step(double time) override;

	~RK4Integrator();

private:
	double* k1 = nullptr;
	double* k2 = nullptr;
	double* k3 = nullptr;
	double* k4 = nullptr;
	double* _states1 = nullptr;
	double* _states2 = nullptr;
	double* _states3 = nullptr;
};

