#pragma once
#include <math.h>

// forward decl
class Vector3D;

class Vector3DView {

public:
	
	// Constructors
	Vector3DView();

	inline double operator[](int i) const { return p[i]; }

	// no copying
	Vector3DView(const Vector3DView& vectorView) = delete;

	void SetPtr(double* ptr);

	// Operator Overlaods Member
	void operator=(const Vector3DView& rhs);
	void operator=(const Vector3D& rhs);

	void operator+=(const Vector3DView& rhs);
	void operator-=(const Vector3DView& rhs);
	void operator*=(double num);
	void operator/=(double num);
	
	//Static Functions
	static double DotProduct(const Vector3DView& v1, const Vector3DView& v2);
	static void CrossProduct(const Vector3DView& lhs, const Vector3DView& rhs, Vector3DView& result);
	
	// Public Functions
	double Norm() const;
	void Normalize();

private:
	double* p;
};

