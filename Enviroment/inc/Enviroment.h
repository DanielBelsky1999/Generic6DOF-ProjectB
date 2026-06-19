#pragma once
#include "AtmosphereFactory.h"
#include "GravityFactory.h"
#include "MagneticFieldFactory.h"

class Enviroment
{
public:
	Enviroment();
	~Enviroment();

	IAtmosphere& Atmosphere();
	IGravity& Gravity();
	IMagneticField& MagneticField();

private:
	IAtmosphere* _atmosphere;
	IGravity* _gravity;
	IMagneticField* _magnetic;
};

