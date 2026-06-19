#pragma once
#include <string>
#include <stdexcept>

enum class EarthType {
	Ellipsoid,
	Flat,
};

EarthType ParseEarthType(const std::string& str);