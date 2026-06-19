#pragma once

#include <math.h>

class Quaternion;

class QuaternionView {

public:
	// Constructors
	QuaternionView();

	// no copying
	QuaternionView(const QuaternionView& QuaternionView) = delete;

	inline double operator[](int i) const { return q[i]; }

	void SetPtr(double* ptr);

	// Operator_Overlaods_Member
	void operator=(const QuaternionView& QuaternionView);
	void operator=(const Quaternion& rhs);

	void operator+=(const QuaternionView& QuaternionView);
	void operator-=(const QuaternionView& QuaternionView);
	void operator*=(const QuaternionView& QuaternionView);
	void operator*=(double num);
	void operator/=(double num);

	// Public Functions
	double Norm() const;
	void Normalize();
	void Conjugate();


private:
	// q0         - the real part
	// q1, q2, q3 - the imaginary part
	double* q;
};
