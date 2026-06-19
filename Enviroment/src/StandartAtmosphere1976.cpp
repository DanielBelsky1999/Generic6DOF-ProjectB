#include "StandartAtmosphere1976.h"

StandartAtmosphere1976::StandartAtmosphere1976(double T_Sealevel_Celsius, double P_Sealevel_Pascals)
{
	CalculateBaseTempPress(T_Sealevel_Celsius, P_Sealevel_Pascals);
}

double StandartAtmosphere1976::GetPressure(double altitude)
{
	int layer_i = GetLayerIndx(altitude);
	double h = GeopotentialAltitude(altitude);

	// if higher than 105 Km ("layer 10")
	if (layer_i == 10)
		return _basePressures[9] * std::exp((-g0 / (R * _baseTemepratures[9])) * (h - _altitudeLayers[9]*1000));

	double h_from_base = h - _altitudeLayers[layer_i]*1000;
	double T0 = _baseTemepratures[layer_i];
	double P0 = _basePressures[layer_i];
	double L = _LapseRates[layer_i];

	if (L == 0) {
		return P0 * std::exp((-g0 / (R * T0)) * h_from_base);
	}
	else { // LapseRate is not zero
		return P0 * std::pow((1 + (L * h_from_base) / T0), (-g0 / (R * L)));
	}
}

double StandartAtmosphere1976::GetTemperature(double altitude)
{
	int layer_i = GetLayerIndx(altitude);
	double h = GeopotentialAltitude(altitude);

	if (layer_i == 10)
		return _baseTemepratures[9];

	double T0 = _baseTemepratures[layer_i];
	double L = _LapseRates[layer_i];

	if (L == 0)
		return T0;
	else {
		return T0 + L * (h - _altitudeLayers[layer_i]*1000);
	}
}

double StandartAtmosphere1976::GetDensity(double altitude)
{
	double T = GetTemperature(altitude);
	double P = GetPressure(altitude);
	return P / (R * T);
}

double StandartAtmosphere1976::GetSpeedOfSound(double altitude)
{
	double T = GetTemperature(altitude);
	return std::sqrt(gamma * R * T);
}

void StandartAtmosphere1976::CalculateBaseTempPress(double T_Sealevel_Celsius, double P_Sealevel_Pascals)
{
	_baseTemepratures[0] = T_Sealevel_Celsius + T_C_K;
	_basePressures[0] = P_Sealevel_Pascals;

	for (int i = 1; i < 10; i++) {
		double layer_width = (_altitudeLayers[i] - _altitudeLayers[i - 1])*1000; // [m]
		double T0 = _baseTemepratures[i - 1];
		double P0 = _basePressures[i - 1];
		double L = _LapseRates[i - 1];

		if (L == 0) {
			_baseTemepratures[i] = T0;
			_basePressures[i] = P0 * std::exp((- g0 / (R * T0))*layer_width);
		}
		else { // LapseRate is not zero
			_baseTemepratures[i] = T0 + L * layer_width;
			_basePressures[i] = P0 * std::pow((1 + (L * layer_width) / T0), (-g0 / (R * L)));
		}
	}
}

double StandartAtmosphere1976::GeopotentialAltitude(double altitude)
{
	return (R_Earth * altitude) / (R_Earth + altitude);
}

int StandartAtmosphere1976::GetLayerIndx(double altitude)
{
	double h = GeopotentialAltitude(altitude);
	if (h >= _altitudeLayers[9] * 1000) return 10;

	int indx = 0;
	while (_altitudeLayers[indx + 1] * 1000 < h) {
		indx++;
	}
	return indx;
}