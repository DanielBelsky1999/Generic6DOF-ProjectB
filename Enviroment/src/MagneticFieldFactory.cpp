#include "MagneticFieldFactory.h"

MagneticFieldType MagneticFieldFactory::ParseMagneticFieldType(const std::string& str)
{
    if (str == "None") return MagneticFieldType::None;
    if (str == "TiltedDipole") return MagneticFieldType::TiltedDipole;
    throw std::runtime_error("Error: World/MagneticField type misconfiguration");
}

IMagneticField* MagneticFieldFactory::CreateMagneticField()
{
    MagneticFieldType magneticFieldType = ParseMagneticFieldType(Initializer::GetType("World/MagneticField"));

    switch (magneticFieldType) {
    case MagneticFieldType::None:
        return new  NoneMagneticField();
    case MagneticFieldType::TiltedDipole:
        return new TiltedDipoleMagneticField();
    default:
        return nullptr;
    }
}


