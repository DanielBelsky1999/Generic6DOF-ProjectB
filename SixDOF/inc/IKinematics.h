#pragma once
#include "IStatefulModel.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "EulerAngles.h"
#include <string>
#include "Constants.h"

struct KinematicsInitData {
	Vector3D position_llh_ddm;
	Vector3D velocity_CG_wrt_NED; // in CG frame
	EulerAngles euler_CGwrtNED; // euler angles of the c.g. frame relative to NED
	Vector3D rate_CGwrtNED; // expressed in CG frame
};

class SixDOF;
class Enviroment;
class IPhysicalPlatform;

class IKinematics : public IStatefulModel
{
public:
	IKinematics(SixDOF* sixDOF, KinematicsInitData kinematicsInitData);

	virtual Vector3D GetPosition() = 0;
	virtual double GetAltitude() = 0;
	virtual Vector3D GetSupportiveFocreBody(double time) = 0;
	virtual Quaternion GetQNB() = 0;

	// for publishing and models
	virtual Vector3D GetLLH() =0;
	virtual Vector3D GetVelocityNED() = 0;
	virtual EulerAngles EulerNED2Body() = 0;
	virtual Vector3D GetWNBB() = 0;

	// for the IMU model
	virtual Vector3D GetAccIMU(double time) = 0;
	virtual Vector3D GetWIBB() = 0;

	virtual std::string GetLogHeader_12() const = 0;

protected:

	KinematicsInitData _kinematics_init;

	IPhysicalPlatform& GetPlatform();
	Enviroment& GetEnviroment();

private:
	SixDOF* _sixDOF;
};

