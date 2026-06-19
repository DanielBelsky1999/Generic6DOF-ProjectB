#pragma once


class SixDOF;


class Integrator
{
public:
	Integrator(SixDOF* sixDOF, double DT);

	virtual void Init(int numStates) = 0;
	virtual void Step(double time) = 0;

	virtual ~Integrator() = default;

protected:
	double _DT;
	int _numStates;
	void CallBindStateVectors(double* new_states, double* new_dStates);
	double* GetSixDOFsStateVector();
	void CallComputeDerivatives(double time);

private:
	SixDOF* _sixDOF;
};

