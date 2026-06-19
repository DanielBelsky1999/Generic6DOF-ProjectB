#include "QuaternionView.h"
#include "Quaternion.h"

QuaternionView::QuaternionView() 
	: q(nullptr)
{

}
void QuaternionView::SetPtr(double* ptr) {
	q = ptr;
};

void QuaternionView::operator=(const QuaternionView& QuaternionView) {
	q[0] = QuaternionView.q[0];
	q[1] = QuaternionView.q[1];
	q[2] = QuaternionView.q[2];
	q[3] = QuaternionView.q[3];
}

void QuaternionView::operator=(const Quaternion& rhs)
{
	q[0] = rhs(0);
	q[1] = rhs(1);
	q[2] = rhs(2);
	q[3] = rhs(3);
}

void QuaternionView::operator+=(const QuaternionView& QuaternionView) {
	q[0] += QuaternionView.q[0];
	q[1] += QuaternionView.q[1];
	q[2] += QuaternionView.q[2];
	q[3] += QuaternionView.q[3];
}
void QuaternionView::operator-=(const QuaternionView& QuaternionView) {
	q[0] -= QuaternionView.q[0];
	q[1] -= QuaternionView.q[1];
	q[2] -= QuaternionView.q[2];
	q[3] -= QuaternionView.q[3];
}
void QuaternionView::operator*=(const QuaternionView& QuaternionView2) {
	double q0_temp = (q[0] * QuaternionView2.q[0]) - (q[1] * QuaternionView2.q[1]) - (q[2] * QuaternionView2.q[2]) - (q[3] * QuaternionView2.q[3]);
	double q1_temp = (q[0] * QuaternionView2.q[1]) + (q[1] * QuaternionView2.q[0]) + (q[2] * QuaternionView2.q[3]) - (q[3] * QuaternionView2.q[2]);
	double q2_temp = (q[0] * QuaternionView2.q[2]) - (q[1] * QuaternionView2.q[3]) + (q[2] * QuaternionView2.q[0]) + (q[3] * QuaternionView2.q[1]);
	double q3_temp = (q[0] * QuaternionView2.q[3]) + (q[1] * QuaternionView2.q[2]) - (q[2] * QuaternionView2.q[1]) + (q[3] * QuaternionView2.q[0]);
	q[0] = q0_temp;
	q[1] = q1_temp;
	q[2] = q2_temp;
	q[3] = q3_temp;
}
void QuaternionView::operator*=(double num) {
	q[0] *= num;
	q[1] *= num;
	q[2] *= num;
	q[3] *= num;
}
void QuaternionView::operator/=(double num) {
	q[0] /= num;
	q[1] /= num;
	q[2] /= num;
	q[3] /= num;
}

double QuaternionView::Norm() const {
	return sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
};
void QuaternionView::Normalize() {
	(*this) /= Norm();
};
void QuaternionView::Conjugate()  {
	q[1] = -q[1];
	q[2] = -q[2];
	q[3] = -q[3];
}