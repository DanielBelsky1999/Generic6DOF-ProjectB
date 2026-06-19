#include "Matrix33.h"

Matrix33::Matrix33() {
    zeroALL();
}

Matrix33::Matrix33(double m_11, double m_12, double m_13,
    double m_21, double m_22, double m_23,
    double m_31, double m_32, double m_33) 
{
    p[0][0] = m_11; p[0][1] = m_12; p[0][2] = m_13;
    p[1][0] = m_21; p[1][1] = m_22; p[1][2] = m_23;
    p[2][0] = m_31; p[2][1] = m_32; p[2][2] = m_33;
}

Matrix33::Matrix33(const Matrix33& m)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] = m.p[i][j];
        }
    }
}

Matrix33& Matrix33::operator=(const Matrix33& m)
{
    if (this == &m) {
        return *this;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

bool Matrix33::operator==(const Matrix33& m)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (p[i][j] != m.p[i][j])
                return false;
        }
    }
    return true;
}

Matrix33& Matrix33::operator+=(const Matrix33& m)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] += m.p[i][j];
        }
    }
    return *this;
}

Matrix33& Matrix33::operator-=(const Matrix33& m)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] -= m.p[i][j];
        }
    }
    return *this;
}

Matrix33& Matrix33::operator*=(const Matrix33& m)
{
    Matrix33 temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                temp.p[i][j] += (p[i][k] * m.p[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix33& Matrix33::operator*=(double num)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] *= num;
        }
    }
    return *this;
}

Matrix33& Matrix33::operator/=(double num)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] /= num;
        }
    }
    return *this;
}

Matrix33 Matrix33::Transpose() const
{
    Matrix33 temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp.p[j][i] = p[i][j];
        }
    }
    return temp;
}
Matrix33 Matrix33::Inverse() const
{
    Matrix33 temp;
    temp.p[0][0] = p[1][1]*p[2][2] - p[1][2] * p[2][1];
    temp.p[0][1] = p[0][2]*p[2][1] - p[0][1] * p[2][2];
    temp.p[0][2] = p[0][1]*p[1][2] - p[0][2] * p[1][1];
    temp.p[1][0] = p[1][2]*p[2][0] - p[1][0] * p[2][2];
    temp.p[1][1] = p[0][0]*p[2][2] - p[0][2] * p[2][0];
    temp.p[1][2] = p[0][2]*p[1][0] - p[0][0] * p[1][2];
    temp.p[2][0] = p[1][0]*p[2][1] - p[1][1] * p[2][0];
    temp.p[2][1] = p[0][1]*p[2][0] - p[0][0] * p[2][1];
    temp.p[2][2] = p[0][0]*p[1][1] - p[0][1] * p[1][0];
    return temp / Determinant();
}
double Matrix33::Determinant() const {
    double temp = p[0][0] * (p[1][1] * p[2][2] - p[1][2] * p[2][1]);
    temp -= p[0][1] * (p[1][0] * p[2][2] - p[1][2] * p[2][0]);
    temp += p[0][2] * (p[1][0] * p[2][1] - p[1][1] * p[2][0]);
    return temp;
}
double Matrix33::Trace() const {
    return  (p[0][0] + p[1][1] + p[2][2]);
}

void Matrix33::zeroALL()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            p[i][j] = 0;
        }
    }
}


Matrix33 operator+(const Matrix33& m1, const Matrix33& m2)
{
    Matrix33 temp(m1);
    return (temp += m2);
}
Matrix33 operator-(const Matrix33& m1, const Matrix33& m2)
{
    Matrix33 temp(m1);
    return (temp -= m2);
}
Matrix33 operator*(const Matrix33& m1, const Matrix33& m2)
{
    Matrix33 temp(m1);
    return (temp *= m2);
}
Matrix33 operator*(const Matrix33& m, double num)
{
    Matrix33 temp(m);
    return (temp *= num);
}
Matrix33 operator*(double num, const Matrix33& m)
{
    return (m * num);
}
Matrix33 operator/(const Matrix33& m, double num)
{
    Matrix33 temp(m);
    return (temp /= num);
}