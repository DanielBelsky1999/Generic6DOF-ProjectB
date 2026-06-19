#pragma once
#include "IAtmosphere.h"
class NoAtmosphere : public IAtmosphere
{
public:
	double GetPressure(double altitude) override { return 0; };
	double GetTemperature(double altitude) override { return 0; };
	double GetDensity(double altitude) override { return 0; };
	double GetSpeedOfSound(double altitude) override { return 0; };
};

