#include "AtmosphereFactory.h"

AtmosphereType AtmosphereFactory::ParseAtmosphereType(const std::string& str)
{
    if (str == "ISA1976") return AtmosphereType::ISA1976;
    if (str == "OffsetISA1976") return AtmosphereType::OffsetISA1976;
    if (str == "Constant") return AtmosphereType::Constant;
    if (str == "None") return AtmosphereType::None;
    throw std::runtime_error("Error: World/Atmosphere type misconfiguration");
}

IAtmosphere* AtmosphereFactory::CreateAtmosphere()
{
    AtmosphereType atmospheretype = ParseAtmosphereType(Initializer::GetType("World/Atmosphere"));
    switch (atmospheretype) {
    case AtmosphereType::ISA1976:
        return new StandartAtmosphere1976();
    case AtmosphereType::OffsetISA1976:
        return new StandartAtmosphere1976(
            Initializer::GetValueAsDouble("World/Atmosphere/OffsetISA1976/TemperatureSeaLevel"),
            Initializer::GetValueAsDouble("World/Atmosphere/OffsetISA1976/PressureSeaLevel"));
    case AtmosphereType::Constant:
        return new ConstantAtmosphere(
            Initializer::GetValueAsDouble("World/Atmosphere/Constant/Temperature"),
            Initializer::GetValueAsDouble("World/Atmosphere/Constant/Pressure"));
    case AtmosphereType::None:
        return new NoAtmosphere();
    default:
        return nullptr;
    }
}