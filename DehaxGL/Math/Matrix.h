#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cmath>
#include "Math/Vec3f.h"

struct Matrix
{
public:
    explicit Matrix(int rows = 4, int cols = 4, bool identity = false);
    
    static Matrix transform(long double x, long double y, long double z);
    static Matrix transform(Vec3f offset);
    static Matrix rotationX(long double angle);
    static Matrix rotationY(long double angle);
    static Matrix rotationZ(long double angle);
    static Matrix rotation(long double angleX, long double angleY, long double angleZ);
    static Matrix rotation(Vec3f rotation);
    static Matrix rotation(Vec3f rotation, Vec3f pivot);
    static Matrix scale(long double x, long double y, long double z);
    static Matrix scale(Vec3f scale);
    static Matrix scale(Vec3f scale, Vec3f pivot);
    
    std::vector<long double> &operator [](const int i);
    Matrix operator *(const Matrix &a);
    
    int rows() const;
    int cols() const;
private:
    std::vector<std::vector<long double>> m;
    int m_rows;
    int m_cols;
};

#endif // MATRIX_H
