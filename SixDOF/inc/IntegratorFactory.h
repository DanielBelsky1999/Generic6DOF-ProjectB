#pragma once
#include "Integrator.h"
#include "Initializer.h"
#include <stdexcept>
#include "EulerIntegrator.h"
#include "RK4Integrator.h"

class SixDOF;

enum class IntegratorType {
	Euler,
	RK4,
};

class IntegratorFactory {
public:
	static Integrator* CreateIntegrator(SixDOF* sixdof);
private:
	static IntegratorType ParseIntegratorType(const std::string& str);
};


