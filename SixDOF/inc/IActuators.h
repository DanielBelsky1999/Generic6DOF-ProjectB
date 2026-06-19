#pragma once
#include "IPhysicalModel.h"
class IActuators : public IPhysicalModel
{
public:
	IActuators(IPhysicalPlatform* platform);

	virtual double GetActuator(int indx) = 0;
};

