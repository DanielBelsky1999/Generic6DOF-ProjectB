#include "Vector3DView.h"
#include "Vector3D.h"


Vector3DView::Vector3DView()
	: p(nullptr)
{
}

void Vector3DView::SetPtr(double* ptr)
{
	p = ptr;
}

void Vector3DView::operator=(const Vector3DView& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] = vector.p[indx];
	}
}

void Vector3DView::operator=(const Vector3D& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] = vector[indx];
	}
}

void Vector3DView::operator+=(const Vector3DView& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] += vector.p[indx];
	}
}

void Vector3DView::operator-=(const Vector3DView& vector) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] -= vector.p[indx];
	}
}

void Vector3DView::operator*=(double num) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] *= num;
	}
}

void Vector3DView::operator/=(double num) {
	for (int indx = 0; indx < 3; indx++) {
		p[indx] /= num;
	}
}

double Vector3DView::DotProduct(const Vector3DView& vector1, const Vector3DView& vector2) {
	return vector1.p[0]*vector2.p[0] + vector1.p[1]*vector2.p[1] + vector1.p[2]*vector2.p[2];
}

void Vector3DView::CrossProduct(const Vector3DView& vector1, const Vector3DView& vector2, Vector3DView& result) {
	
	double v0 = vector1.p[1] * vector2.p[2] - vector1.p[2] * vector2.p[1];
	double v1 = -(vector1.p[0] * vector2.p[2] - vector1.p[2] * vector2.p[0]);
	double v2 = vector1.p[0] * vector2.p[1] - vector1.p[1] * vector2.p[0];
	result.p[0] = v0;
	result.p[1] = v1;
	result.p[2] = v2;
}

double Vector3DView::Norm() const {
	return sqrt(p[0]*p[0] + p[1]*p[1] + p[2]*p[2]);
}
void Vector3DView::Normalize() {
	(*this) /= Norm();
}
