#pragma once
class IAtmosphere
{
public: 
	virtual double GetPressure(double altitude) = 0;
	virtual double GetTemperature(double altitude) = 0;
	virtual double GetDensity(double altitude) = 0;
	virtual double GetSpeedOfSound(double altitude) = 0;
};

