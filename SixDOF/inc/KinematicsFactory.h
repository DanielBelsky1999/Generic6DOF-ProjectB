#pragma once
#include <stdexcept>
#include "EarthType.h"
#include "IKinematics.h"
#include "Initializer.h"
#include "ECEFKinematics.h"
#include "FlatEarthKinematics.h"

class SixDOF;
struct KinematicsInitData;

class KinematicsFactory
{
public:
	static IKinematics* CreateKinematics(SixDOF* sixdof, KinematicsInitData kinematics_init_data);
};

