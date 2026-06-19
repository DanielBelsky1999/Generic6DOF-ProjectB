#pragma once

#include "Matrix33.h"
#include "Vector3D.h"
#include "Quaternion.h"

// Misc Operators
Vector3D operator*(const Matrix33&, const Vector3D&);
Quaternion operator*(const Quaternion&, const Vector3D&);
