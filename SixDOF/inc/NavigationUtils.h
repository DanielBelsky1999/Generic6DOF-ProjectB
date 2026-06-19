#pragma once
#include "Vector3D.h"
#include "Quaternion.h"
#include "Constants.h"
#include "EulerAngles.h"
#include "nav_math_operators.h"
#include "LinearAlgebraOps.h"
#include <math.h>

class NavigationUtils
{
public:

	static Vector3D LLH_to_ECEF(const Vector3D& llh_ddm);
	static Vector3D ECEF_to_LLH(const Vector3D& ecef);

	static Quaternion EulerwrtNED_to_qeb(const EulerAngles& euler, const Vector3D& llh_ddm);
	static Vector3D BodyVelwrtNED_to_ECEF(const EulerAngles& euler, const Vector3D& llh_ddm, const Vector3D& velBodywrtNED);
	static Vector3D W_NB_B_to_W_IB_B(const Vector3D& W_IE_E, const Vector3D& w_nb_b, const EulerAngles& euler, const Vector3D& llh_ddm, const Vector3D& velCGwrtNED_body);

	static Vector3D W_IB_B_to_W_NB_B(const Vector3D& W_IE_E, const Vector3D& w_ib_b, const EulerAngles& euler, const Vector3D& llh, const Vector3D& velCGwrtNED_body);

	static EulerAngles qeb_to_EulerwrtNED(const Quaternion& qeb, const Vector3D& ecef);

	static Vector3D ECEF_to_NED(const Vector3D& v_ECEF, const Vector3D& ecef_position);

	static Vector3D XYZ_to_LLH(const Vector3D& XYZ, const Vector3D& origin_llh);

private:
	static double RN(const Vector3D& llh_ddm);
	static double RM(const Vector3D& llh_ddm);

};

