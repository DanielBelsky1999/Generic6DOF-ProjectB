#pragma once
#include "IAtmosphere.h"
#include <cmath>

class ConstantAtmosphere : public IAtmosphere
{
public:
	ConstantAtmosphere(double T_Celsius, double P_Pascals);

	double GetPressure(double altitude) override { return P; };
	double GetTemperature(double altitude) override { return T; };
	double GetDensity(double altitude) override;
	double GetSpeedOfSound(double altitude) override;
private:
	static constexpr double R = 287.05287; // [J/KgK]
	static constexpr double T_C_K = 273.15; // C to K
	static constexpr double gamma = 1.4;

	double T, P;
};

