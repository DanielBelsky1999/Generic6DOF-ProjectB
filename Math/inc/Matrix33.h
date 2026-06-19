#pragma once

class Matrix33 {
public:

    Matrix33();
    Matrix33(double m_11, double m_12, double m_13,
             double m_21, double m_22, double m_23,
             double m_31, double m_32, double m_33);
    Matrix33(const Matrix33& m);

    inline double operator()(int x, int y) const { return p[x][y]; };
    
    Matrix33& operator=(const Matrix33& m);
    bool operator==(const Matrix33& m);
    Matrix33& operator+=(const Matrix33& m);
    Matrix33& operator-=(const Matrix33& m);
    Matrix33& operator*=(const Matrix33& m);
    Matrix33& operator*=(double num);
    Matrix33& operator/=(double num);

    Matrix33 Transpose() const;
    Matrix33 Inverse() const;
    double Determinant() const;
    double Trace() const;

protected:
    double p[3][3];
    void zeroALL();
};

// Matrix33 Operators
Matrix33 operator+(const Matrix33&, const Matrix33&);
Matrix33 operator-(const Matrix33&, const Matrix33&);
Matrix33 operator*(const Matrix33&, const Matrix33&);
Matrix33 operator*(const Matrix33&, double);
Matrix33 operator*(double, const Matrix33&);
Matrix33 operator/(const Matrix33&, double);
