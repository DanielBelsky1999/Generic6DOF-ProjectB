#include "LinearAlgebraOps.h"

Vector3D operator*(const Matrix33& m, const Vector3D& v) {
    Vector3D temp(m(0, 0) * v[0] + m(0, 1) * v[1] + m(0, 2) * v[2],
                  m(1, 0) * v[0] + m(1, 1) * v[1] + m(1, 2) * v[2],
                  m(2, 0) * v[0] + m(2, 1) * v[1] + m(2, 2) * v[2]);
    return temp;
}

Quaternion operator*(const Quaternion& q, const Vector3D& v) {
    Quaternion rhs(0, v[0], v[1], v[2]);
    return q * rhs;
}

