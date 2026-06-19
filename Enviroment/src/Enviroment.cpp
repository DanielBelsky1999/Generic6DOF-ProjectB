#include "Enviroment.h"

Enviroment::Enviroment()
{
	_gravity = GravityFactory::CreateGravity();
	_atmosphere = AtmosphereFactory::CreateAtmosphere();
	_magnetic = MagneticFieldFactory::CreateMagneticField();
}

Enviroment::~Enviroment()
{
	delete _gravity;
	delete _atmosphere;
	delete _magnetic;
}

IAtmosphere& Enviroment::Atmosphere()
{
	return *_atmosphere;
}

IGravity& Enviroment::Gravity()
{
	return *_gravity;
}

IMagneticField& Enviroment::MagneticField()
{
	return *_magnetic;
}