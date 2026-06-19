#include "TiltedDipoleMagneticField.h"

TiltedDipoleMagneticField::TiltedDipoleMagneticField()
{
	EulerAngles MagneticDipoleAngles(-72.0 * PI / 180.0, -80.0 * PI / 180.0, 0);
	Quaternion q_ecef_magnetic = QuaternionFromEuler(MagneticDipoleAngles);
	double M = 7.94e22;
	m = ImaginaryFromQuaternion(q_ecef_magnetic * Vector3D(M, 0, 0) * q_ecef_magnetic.Conjugate());
}

Vector3D TiltedDipoleMagneticField::GetMagneticField_sensor(const Vector3D& llh, const Quaternion& q_ns)
{

	Vector3D position_ecef = NavigationUtils::LLH_to_ECEF(Vector3D(llh[0] * RAD2DEG, llh[1] * RAD2DEG, llh[2]));

	double r = position_ecef.Norm();
	position_ecef.Normalize();

	constexpr double  mu0over4PI = 1e-7; //  = 1.25663706127e-6 / (4.0 * PI);

	Vector3D B_ecef = mu0over4PI / (r * r * r) * (3 * position_ecef * Vector3D::DotProduct(m, position_ecef) - m);

	Quaternion q_en = QuaternionFromEuler(EulerAngles(llh[1], -(llh[0] + PI / 2), 0));

	Quaternion q_es = q_en * q_ns;

	return ImaginaryFromQuaternion(q_es.Conjugate() * B_ecef * q_es);
}
