#include "ConstantAtmosphere.h"

ConstantAtmosphere::ConstantAtmosphere(double T_Celsius, double P_Pascals) : T(T_Celsius+T_C_K), P(P_Pascals)
{
}

double ConstantAtmosphere::GetDensity(double altitude)
{
	return P / (R * T);
}

double ConstantAtmosphere::GetSpeedOfSound(double altitude)
{
	return std::sqrt(gamma * R * T);
}
