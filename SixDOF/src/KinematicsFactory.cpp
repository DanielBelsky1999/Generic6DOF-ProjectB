#include "KinematicsFactory.h"

IKinematics* KinematicsFactory::CreateKinematics(SixDOF* sixdof, KinematicsInitData kinematics_init_data)
{
    EarthType earthtype = ParseEarthType(Initializer::GetType("World/Earth"));
    switch (earthtype) {
    case EarthType::Ellipsoid:
        return new ECEFKinematics(sixdof, kinematics_init_data);
    case EarthType::Flat:
        return new FlatEarthKinematics(sixdof, kinematics_init_data);
    default:
        return nullptr;
    }
}
