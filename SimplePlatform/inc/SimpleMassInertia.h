#pragma once
#include "IMassInertia.h"
#include "IStatefulModel.h"
#include "Vector3D.h"
#include "Matrix33.h"
#include "DoubleView.h"

class SimpleMassInertia : public IMassInertia, public IStatefulModel
{
public:

	SimpleMassInertia(IPhysicalPlatform* platform);

	double GetMass(double time) const override;
	Matrix33 GetInertiaCG(double time) const override;
	Matrix33 GetInertiaInverse(double time) const override;
	Vector3D CG(double time) const override;

	int GetStateNumber() override;

	void SetStatesAndDerivatives(double* states, double* dStates) override;
	void ComputeDerivatives(double time) override;

	void InitializeStates(double* states) override;
	void PostIntegrationUpdate(double* states) override;

private:
	void SetStates(double* states) override;

private:
	static constexpr int NUM_OF_STATES = 1;

	// states
	DoubleView mass;
	// state derivatives
	DoubleView dmass;

};

