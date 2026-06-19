#pragma once
#include "IAtmosphere.h"
#include <cmath>

class StandartAtmosphere1976 : public IAtmosphere
{
public:
	StandartAtmosphere1976(double T_Sealevel_Celsius = 15.0, double P_Sealevel_Pascals = 101325);

	double GetPressure(double altitude) override;
	double GetTemperature(double altitude) override;
	double GetDensity(double altitude) override;
	double GetSpeedOfSound(double altitude) override;

private:
	static constexpr double R = 287.05287; // [J/KgK]
	static constexpr double T_C_K = 273.15; // C to K
	static constexpr double g0 = 9.8066; // [m/s^2] Assume const. g0 for now. Later make that latitude dependent. 
	static constexpr double R_Earth = 6356766.0; // [m]
	static constexpr double gamma = 1.4;

	const double _altitudeLayers[10] = { 0.0, 11.0, 20.0, 32.0, 47.0, 51.0, 71.0, 84.852, 90.0, 105.0 }; // [Km]
	const double _LapseRates[9] = { -0.0065, 0.0, 0.001, 0.0028, 0.0, -0.0028, -0.002, 0.0, 0.004}; // [deg / m]
	double _baseTemepratures[10];
	double _basePressures[10];

	void CalculateBaseTempPress(double T_Sealevel_Celsius, double P_Sealevel_Pascals);
	double GeopotentialAltitude(double altitude);
	int GetLayerIndx(double altitude);
};

