#include "IntegratorFactory.h"


IntegratorType IntegratorFactory::ParseIntegratorType(const std::string& str)
{
    if (str == "Euler") return IntegratorType::Euler;
    if (str == "RK4") return IntegratorType::RK4;
    throw std::runtime_error("Error: Integrator type misconfiguration");
}

Integrator* IntegratorFactory::CreateIntegrator(SixDOF* sixdof)
{
    IntegratorType type = ParseIntegratorType(Initializer::GetType("Integrator"));
    double DT = Initializer::GetValueAsDouble("Integrator/DT");
    switch (type) {
    case IntegratorType::Euler:
        return new EulerIntegrator(sixdof,DT);
    case IntegratorType::RK4:
        return new RK4Integrator(sixdof, DT);
    default:
        return nullptr;
    }
}

