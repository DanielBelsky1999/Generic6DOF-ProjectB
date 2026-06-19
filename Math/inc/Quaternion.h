#pragma once

#include <math.h>

class QuaternionView;

class Quaternion {

public:
	// Constructors
	Quaternion();
	Quaternion(double q0_real, double q1, double q2, double q3);

	Quaternion(const Quaternion& quaternion);
	explicit Quaternion(const QuaternionView& quaternionView);

	inline double operator()(int x) const { return q[x]; };

	// Operator_Overlaods_Member
	Quaternion& operator=(const Quaternion& quaternion);
	Quaternion& operator+=(const Quaternion& quaternion);
	Quaternion& operator-=(const Quaternion& quaternion);
	Quaternion& operator*=(const Quaternion& quaternion);
	Quaternion& operator*=(double num);
	Quaternion& operator/=(double num);

	// Public Functions
	double Norm() const;
	void Normalize();
	Quaternion Conjugate() const;
	Quaternion UnitQuaternion() const;


private:
	// q0         - the real part
	// q1, q2, q3 - the imaginary part
	double q[4];
};

Quaternion operator+(const Quaternion&, const Quaternion&);
Quaternion operator-(const Quaternion&, const Quaternion&);
Quaternion operator*(const Quaternion&, double);
Quaternion operator*(double, const Quaternion&);
Quaternion operator*(const Quaternion&, const Quaternion&);
Quaternion operator/(const Quaternion&, double);