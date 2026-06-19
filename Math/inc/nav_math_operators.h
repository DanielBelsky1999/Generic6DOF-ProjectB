#pragma once

#include <math.h>
#include "Matrix33.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "EulerAngles.h"

Vector3D ImaginaryFromQuaternion(const Quaternion& q);

Matrix33 MatrixFromQuaternion(const Quaternion& q);
Quaternion QuaternionFromMatrix(const Matrix33& m);

Matrix33 MatrixFromEuler(const EulerAngles& e);
EulerAngles EulerFromMatrix(const Matrix33& m);

EulerAngles EulerFromQuaternions(const Quaternion& q);
Quaternion QuaternionFromEuler(const EulerAngles& e);