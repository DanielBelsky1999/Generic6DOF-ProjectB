#pragma once
#include "INormal.h"
#include "IStatelessModel.h"
#include "NavigationUtils.h"

/// <summary>
/// This verz simplistic model assumes that the height you start at is your ground. 
/// The normal is getting disables as soon you leave the ground.
/// </summary>
class SimpleNormal : public INormal, public IStatelessModel
{
public:
	SimpleNormal(IPhysicalPlatform* platform);

	Vector3D GetNormalBody(double time) override;

};

