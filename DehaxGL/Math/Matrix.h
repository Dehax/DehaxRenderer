#ifndef MATRIX_H
#define MATRIX_H

#include "dehaxgl_global.h"
#include <vector>
#include "Vec3f.h"

struct DEHAXGLSHARED_EXPORT Matrix
{
public:
    explicit Matrix(int rows = 4, int cols = 4, bool identity = false);
//    Matrix &operator=(const Matrix &a);
    
    static Matrix transform(const long double &x, const long double &y, const long double &z);
    static Matrix transform(const Vec3f &offset);
    static Matrix rotationX(const long double &angle);
    static Matrix rotationY(const long double &angle);
    static Matrix rotationZ(const long double &angle);
    static Matrix rotation(const long double &angleX, const long double &angleY, const long double &angleZ);
    static Matrix rotation(Vec3f &rotation);
    static Matrix rotation(Vec3f &rotation, Vec3f &pivot);
    static Matrix scale(const long double &x, const long double &y, const long double &z);
    static Matrix scale(Vec3f &scale);
    static Matrix scale(Vec3f &scale, Vec3f &pivot);
    
    std::vector<long double> &operator[](const int i);
    Matrix operator*(const Matrix &a);
    
    int rows() const;
    int cols() const;
private:
    std::vector<std::vector<long double>> m;
    int m_rows;
    int m_cols;
};

#endif // MATRIX_H
