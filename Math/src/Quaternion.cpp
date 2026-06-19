#include "Quaternion.h"
#include "QuaternionView.h"

Quaternion::Quaternion() {
	q[0] = 1;
	q[1] = 0;
	q[2] = 0;
	q[3] = 0;
}
Quaternion::Quaternion(double q0_real, double q1, double q2, double q3) {
	q[0] = q0_real;
	q[1] = q1;
	q[2] = q2;
	q[3] = q3;
}

Quaternion::Quaternion(const Quaternion& quaternion) {
	q[0] = quaternion.q[0];
	q[1] = quaternion.q[1];
	q[2] = quaternion.q[2];
	q[3] = quaternion.q[3];
}

Quaternion::Quaternion(const QuaternionView& quaternionView)
{
	q[0] = quaternionView[0];
	q[1] = quaternionView[1];
	q[2] = quaternionView[2];
	q[3] = quaternionView[3];
}

Quaternion& Quaternion::operator=(const Quaternion& quaternion) {
	// If same quaternion is being assigned
	if (this == &quaternion) {
		return *this;
	}

	q[0] = quaternion.q[0];
	q[1] = quaternion.q[1];
	q[2] = quaternion.q[2];
	q[3] = quaternion.q[3];
	return *this;
}

Quaternion& Quaternion::operator+=(const Quaternion& quaternion) {
	q[0] += quaternion.q[0];
	q[1] += quaternion.q[1];
	q[2] += quaternion.q[2];
	q[3] += quaternion.q[3];
	return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& quaternion) {
	q[0] -= quaternion.q[0];
	q[1] -= quaternion.q[1];
	q[2] -= quaternion.q[2];
	q[3] -= quaternion.q[3];
	return *this;
}
Quaternion& Quaternion::operator*=(const Quaternion& quaternion2) {
	double q0_temp = (q[0] * quaternion2.q[0]) - (q[1] * quaternion2.q[1]) - (q[2] * quaternion2.q[2]) - (q[3] * quaternion2.q[3]);
	double q1_temp = (q[0] * quaternion2.q[1]) + (q[1] * quaternion2.q[0]) + (q[2] * quaternion2.q[3]) - (q[3] * quaternion2.q[2]);
	double q2_temp = (q[0] * quaternion2.q[2]) - (q[1] * quaternion2.q[3]) + (q[2] * quaternion2.q[0]) + (q[3] * quaternion2.q[1]);
	double q3_temp = (q[0] * quaternion2.q[3]) + (q[1] * quaternion2.q[2]) - (q[2] * quaternion2.q[1]) + (q[3] * quaternion2.q[0]);
	q[0] = q0_temp;
	q[1] = q1_temp;
	q[2] = q2_temp;
	q[3] = q3_temp;
	return (*this);
}
Quaternion& Quaternion::operator*=(double num) {
	q[0] *= num;
	q[1] *= num;
	q[2] *= num;
	q[3] *= num;
	return *this;
}
Quaternion& Quaternion::operator/=(double num) {
	q[0] /= num;
	q[1] /= num;
	q[2] /= num;
	q[3] /= num;
	return *this;
}

double Quaternion::Norm() const {
	return sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
};
void Quaternion::Normalize() {
	(*this) /= Norm();
};
Quaternion Quaternion::Conjugate() const {
	return Quaternion(q[0], -q[1], -q[2], -q[3]);
}

Quaternion Quaternion::UnitQuaternion() const {
	Quaternion temp(q[0], q[1], q[2], q[3]);
	temp.Normalize();
	return temp;
};

Quaternion operator+(const Quaternion& quaternion1, const Quaternion& quaternion2) {
	Quaternion temp(quaternion1);
	return (temp += quaternion2);
};
Quaternion operator-(const Quaternion& quaternion1, const Quaternion& quaternion2) {
	Quaternion temp(quaternion1);
	return (temp -= quaternion2);
};
Quaternion operator*(const Quaternion& quaternion, double num) {
	Quaternion temp(quaternion);
	return (temp *= num);
};
Quaternion operator*(double num, const Quaternion& quaternion) {
	return (quaternion * num);
}
Quaternion operator*(const Quaternion& quaternion1, const Quaternion& quaternion2) {
	Quaternion temp(quaternion1);
	return (temp *= quaternion2);
}
Quaternion operator/(const Quaternion& quaternion, double num) {
	Quaternion temp(quaternion);
	return (temp /= num);
};