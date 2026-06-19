#pragma once
#include <stdexcept>
#include "IAtmosphere.h"
#include "Initializer.h"
#include "StandartAtmosphere1976.h"
#include "ConstantAtmosphere.h"
#include "NoAtmosphere.h"

enum class AtmosphereType {
	ISA1976,
	OffsetISA1976,
	Constant,
	None,
};

class AtmosphereFactory {
public:
	static IAtmosphere* CreateAtmosphere();
private:
	static AtmosphereType ParseAtmosphereType(const std::string& str);
};


