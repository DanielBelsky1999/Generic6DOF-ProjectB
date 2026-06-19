#include "nav_math_operators.h"


Vector3D ImaginaryFromQuaternion(const Quaternion& q)
{
	return Vector3D(q(1), q(2), q(3));
}

Matrix33 MatrixFromQuaternion(const Quaternion& q) {
	return Matrix33(
		q(0) * q(0) + q(1) * q(1) - q(2) * q(2) - q(3) * q(3), 2 * q(3) * q(0) + 2 * q(1) * q(2), 2 * q(1) * q(3) - 2 * q(0) * q(2),
		2 * q(1) * q(2) - 2 * q(3) * q(0), q(0) * q(0) - q(1) * q(1) + q(2) * q(2) - q(3) * q(3), 2 * q(1) * q(0) + 2 * q(3) * q(2),
		2 * q(0) * q(2) + 2 * q(1) * q(3), 2 * q(2) * q(3) - 2 * q(0) * q(1), q(0) * q(0) - q(1) * q(1) - q(2) * q(2) + q(3) * q(3)
	);
}

Quaternion QuaternionFromMatrix(const Matrix33& m) {
	double q0 = sqrt((m.Trace() + 1) / 4);
	double q1 = (m(1, 2) - m(2, 1)) / (4 * q0);
	double q2 = (m(2, 0) - m(0, 2)) / (4 * q0);
	double q3 = (m(0, 1) - m(1, 0)) / (4 * q0);
	return Quaternion(q0, q1, q2, q3);
}

Matrix33 MatrixFromEuler(const EulerAngles& e) {

	double cpsi = cos(e.psi);
	double spsi = sin(e.psi);

	double ctheta = cos(e.theta);
	double stheta = sin(e.theta);

	double cphi = cos(e.phi);
	double sphi = sin(e.phi);

	double a00 = ctheta * cpsi;
	double a01 = ctheta * spsi;
	double a02 = -stheta;

	double a10 = sphi * stheta * cpsi - cphi * spsi;
	double a11 = sphi * stheta * spsi + cphi * cpsi;
	double a12 = sphi * ctheta;

	double a20 = cphi * stheta * cpsi + sphi * spsi;
	double a21 = cphi * stheta * spsi - sphi * cpsi;
	double a22 = cphi * ctheta;

	return Matrix33(a00, a01, a02, a10, a11, a12, a20, a21, a22);
}

EulerAngles EulerFromMatrix(const Matrix33& m) {
	double theta = -asin(m(0, 2));
	double psi = atan2(m(0, 1), m(0, 0));
	double phi = atan2(m(1, 2), m(2, 2));
	return EulerAngles(psi, theta, phi);
}

EulerAngles EulerFromQuaternions(const Quaternion& q) {

	double sinr_cosp = 2 * (q(0) * q(1) + q(2) * q(3));
	double cosr_cosp = 1 - 2 * (q(1) * q(1) + q(2) * q(2));
	double phi = atan2(sinr_cosp, cosr_cosp);
	
	double theta = asin(fmax(-1.0, fmin(1.0, 2.0 * (q(0) * q(2) - q(1) * q(3)))));

	double siny_cosp = 2 * (q(0) * q(3) + q(1) * q(2));
	double cosy_cosp = 1 - 2 * (q(2) * q(2) + q(3) * q(3));
	double psi = atan2(siny_cosp, cosy_cosp);

	return EulerAngles(psi, theta, phi);
}

Quaternion QuaternionFromEuler(const EulerAngles& e) {
	double cy = cos(e.psi * 0.5);
	double sy = sin(e.psi * 0.5);
	double cp = cos(e.theta * 0.5);
	double sp = sin(e.theta * 0.5);
	double cr = cos(e.phi * 0.5);
	double sr = sin(e.phi * 0.5);

	return Quaternion(
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy
	);
}

