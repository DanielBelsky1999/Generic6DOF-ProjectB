#pragma once
#include <stdexcept>
#include "EarthType.h"
#include "IGravity.h"
#include "Initializer.h"
#include "ConstantEarthCentricGravity.h"
#include "NewtonianEarthCentricGravity.h"
#include "NewtonianNormal.h"
#include "NoGravity.h"
#include "ConstantGravity.h"

enum class GravityType {
	ConstantEarthCentric,
	NewtonianEarthCentric,
	NewtonianNormal,
	None,
	Constant,
};

class GravityFactory {
public:
	static IGravity* CreateGravity();
private:
	static GravityType ParseGravityType(const std::string& str);
};


