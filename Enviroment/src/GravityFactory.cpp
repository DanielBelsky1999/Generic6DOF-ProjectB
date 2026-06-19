#include "GravityFactory.h"

GravityType GravityFactory::ParseGravityType(const std::string& str) {
    if (str == "ConstantEarthCentric") return GravityType::ConstantEarthCentric;
    if (str == "NewtonianEarthCentric") return GravityType::NewtonianEarthCentric;
    if (str == "NewtonianNormal") return GravityType::NewtonianNormal;
    if (str == "None") return GravityType::None;
    if (str == "Constant") return GravityType::Constant;
    throw std::runtime_error("Error: World/Earth/Flat-or-Ellipsoid/Gravity  misconfiguration");
}

IGravity* GravityFactory::CreateGravity() {

    EarthType earthtype = ParseEarthType(Initializer::GetType("World/Earth"));
    GravityType gravitytype;
    if (earthtype == EarthType::Ellipsoid) {
        gravitytype = ParseGravityType(Initializer::GetValueAsString("World/Earth/Ellipsoid/Gravity"));
    }
    if (earthtype == EarthType::Flat) {
        gravitytype = ParseGravityType(Initializer::GetValueAsString("World/Earth/Flat/Gravity"));
    }
    switch (gravitytype) {
    case GravityType::ConstantEarthCentric:
        return new  ConstantEarthCentricGravity();
    case GravityType::NewtonianEarthCentric:
        return new NewtonianEarthCentric();
    case GravityType::NewtonianNormal:
        return new NewtonianNormal();
    case GravityType::None:
        return new NoGravity();
    case GravityType::Constant:
        return new ConstantGravity();
    default:
        return nullptr;
    }
}
