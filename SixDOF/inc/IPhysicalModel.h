#pragma once

class IPhysicalPlatform;
class IMassInertia;
class IPropulsion;
class IAerodynamics;
class IActuators;
class INormal;
class IKinematics;
class Enviroment;
struct TControls;

class IPhysicalModel
{
public:
	IPhysicalModel(IPhysicalPlatform* platform);
	virtual ~IPhysicalModel() = default;

protected:

	IMassInertia& GetMassInertia();
	IPropulsion& GetPropulsion();
	IAerodynamics& GetAerodynamics();
	IActuators& GetActuators();
	IKinematics& GetKinematics();
	Enviroment& GetEnviroment();
	TControls& GetControls();

private:
	IPhysicalPlatform* _platform;
};

