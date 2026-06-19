#pragma once
#include <math.h>

// forward decl
class Vector3DView;

class Vector3D {

public:
	
	// Constructors
	Vector3D();
	Vector3D(double v1, double v2, double v3);
	Vector3D(const Vector3D& vector);
	explicit Vector3D(const Vector3DView& vectorView);

	inline double operator[](int i) const { return p[i]; }

	// Operator_Overlaods_Member
	Vector3D& operator=(const Vector3D&);
	Vector3D& operator+=(const Vector3D&);
	Vector3D& operator-=(const Vector3D&);
	Vector3D& operator*=(double);
	Vector3D& operator/=(double);	
	
	//Static_Functions
	static double DotProduct(const Vector3D&, const Vector3D&);
	static Vector3D CrossProduct(const Vector3D&, const Vector3D&);
	
	// Public Functions
	double Norm() const;
	void Normalize();
	Vector3D UnitVec();

private:
	double p[3];
	void zeroALL();
};

// Vector3D Operators
Vector3D operator+(const Vector3D&, const Vector3D&);
Vector3D operator-(const Vector3D&, const Vector3D&);
Vector3D operator*(const Vector3D&, double);
Vector3D operator*(double, const Vector3D&);
Vector3D operator/(const Vector3D&, double);
Vector3D operator-(const Vector3D&);
