#include "EarthType.h"

EarthType ParseEarthType(const std::string& str) {
    if (str == "Ellipsoid") return EarthType::Ellipsoid;
    if (str == "Flat") return EarthType::Flat;
    throw std::runtime_error("Error: World/Earth type misconfiguration");
}