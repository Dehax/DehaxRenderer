#ifndef MATRIX_H
#define MATRIX_H

#include "dehaxgl_global.h"
#include <vector>
#include "Vec3f.h"

struct DEHAXGLSHARED_EXPORT Matrix
{
public:
    explicit Matrix(bool identity = false);
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
    
    //std::vector<long double> &operator[](const int i);
    void set(const int &i, const int &j, const long double &value)
    {
        m[i][j] = value;
    }

    inline long double get(const int &i, const int &j)
    {
        return m[i][j];
    }

    Matrix operator*(const Matrix &a);
    
    
//    int rows() const;
//    int cols() const;
private:
    long double m[4][4];
//    int m_rows;
//    int m_cols;
};

#endif // MATRIX_H
