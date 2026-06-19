#include "Vector3D.h"
#include "Vector3DView.h"

Vector3D::Vector3D() {
	zeroALL();
}

Vector3D::Vector3D(double v1, double v2, double v3) {
	p[0] = v1;
	p[1] = v2;
	p[2] = v3;
}

Vector3D::Vector3D(const Vector3D& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] = vector.p[indx];
	}
}

Vector3D::Vector3D(const Vector3DView& vectorView)
{
	p[0] = vectorView[0];
	p[1] = vectorView[1];
	p[2] = vectorView[2];
}

Vector3D& Vector3D::operator=(const Vector3D& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] = vector.p[indx];
	}
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] += vector.p[indx];
	}
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] -= vector.p[indx];
	}
	return *this;
}

Vector3D& Vector3D::operator*=(double num) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] *= num;
	}
	return *this;
}

Vector3D& Vector3D::operator/=(double num) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] /= num;
	}
	return *this;
}

double Vector3D::DotProduct(const Vector3D& vector1, const Vector3D& vector2) {
	return vector1.p[0]*vector2.p[0] + vector1.p[1]*vector2.p[1] + vector1.p[2]*vector2.p[2];
}
Vector3D Vector3D::CrossProduct(const Vector3D& vector1, const Vector3D& vector2) {
	Vector3D temp(vector1.p[1] * vector2.p[2] - vector1.p[2] * vector2.p[1],
				-(vector1.p[0] * vector2.p[2] - vector1.p[2] * vector2.p[0]),
				 (vector1.p[0] * vector2.p[1] - vector1.p[1] * vector2.p[0]));
	return temp;
}

double Vector3D::Norm() const {
	return sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}
void Vector3D::Normalize() {
	(*this) /= Norm();
}
Vector3D Vector3D::UnitVec() {
	Vector3D temp(p[0], p[1], p[2]);
	temp.Normalize();
	return temp;
}

void Vector3D::zeroALL()
{
	for (int i = 0; i < 3; i++) {
		p[i] = 0;
	}
}


Vector3D operator+(const Vector3D& vector1, const Vector3D& vector2) {
	Vector3D temp(vector1);
	return (temp += vector2);
}
Vector3D operator-(const Vector3D& vector1, const Vector3D& vector2)
{
	Vector3D temp(vector1);
	return (temp -= vector2);
}
Vector3D operator*(double num, const Vector3D& vector)
{
	Vector3D temp(vector);
	return (temp *= num);
}
Vector3D operator*(const Vector3D& vector, double num)
{
	return (num * vector);
}
Vector3D operator/(const Vector3D& vector, double num)
{
	Vector3D temp(vector);
	return (temp /= num);
}
Vector3D operator-(const Vector3D& vector) {
	Vector3D temp(vector);
	return (temp *= (-1));
}
