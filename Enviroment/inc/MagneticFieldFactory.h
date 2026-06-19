#pragma once
#include <stdexcept>
#include "Initializer.h"
#include "IMagneticField.h"
#include "NoneMagneticField.h"
#include "TiltedDipoleMagneticField.h"

enum class MagneticFieldType {
	None,
	TiltedDipole,
};

class MagneticFieldFactory
{
public:
	static IMagneticField* CreateMagneticField();
private:
	static MagneticFieldType ParseMagneticFieldType(const std::string& str);
};

