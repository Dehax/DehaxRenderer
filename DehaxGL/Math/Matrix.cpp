#include "Matrix.h"

Matrix::Matrix(bool identity)/*
    : m(std::vector<std::vector<long double>>(rows, std::vector<long double>(cols, 0.0L))),
      m_rows(rows), m_cols(cols)*/
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = 0.0L;
        }
    }
    
    if (/*rows == cols && */identity) {
        for (int i = 0; i < 4/*rows*/; i++) {
            m[i][i] = 1.0L;
        }
    }
}

//Matrix &Matrix::operator=(const Matrix &a)
//{
//    if (this != &a) {
//        m = a.m;
//        m_rows = a.m_rows;
//        m_cols = a.m_cols;
//    }
    
//    return *this;
//}

Matrix Matrix::transform(const long double &x, const long double &y, const long double &z)
{
    Matrix result = Matrix(/*4, 4, */true);
    
    result.m[3][0] = x;
    result.m[3][1] = y;
    result.m[3][2] = z;
    
    return result;
}

Matrix Matrix::transform(const Vec3f &offset)
{
    return transform(offset.x, offset.y, offset.z);
}

Matrix Matrix::rotationX(const long double &angle)
{
    Matrix result = Matrix(/*4, 4, */true);
    
    long double cosAngle = std::cos(angle);
    long double sinAngle = std::sin(angle);
    
    result.m[1][1] = cosAngle;
    result.m[1][2] = sinAngle;
    result.m[2][1] = -sinAngle;
    result.m[2][2] = cosAngle;
    
    return result;
}

Matrix Matrix::rotationY(const long double &angle)
{
    Matrix result = Matrix(/*4, 4, */true);
    
    long double cosAngle = std::cos(angle);
    long double sinAngle = std::sin(angle);
    
    result.m[0][0] = cosAngle;
    result.m[0][2] = -sinAngle;
    result.m[2][0] = sinAngle;
    result.m[2][2] = cosAngle;
    
    return result;
}

Matrix Matrix::rotationZ(const long double &angle)
{
    Matrix result = Matrix(/*4, 4, */true);
    
    long double cosAngle = std::cos(angle);
    long double sinAngle = std::sin(angle);
    
    result.m[0][0] = cosAngle;
    result.m[1][0] = sinAngle;
    result.m[0][1] = -sinAngle;
    result.m[1][1] = cosAngle;
    
    return result;
}

Matrix Matrix::rotation(const long double &angleX, const long double &angleY, const long double &angleZ)
{
    return rotationX(angleX) * rotationY(angleY) * rotationZ(angleZ);
}

Matrix Matrix::rotation(Vec3f &rotation)
{
    return Matrix::rotation(rotation.x, rotation.y, rotation.z);
}

Matrix Matrix::rotation(Vec3f &rotation, Vec3f &pivot)
{
    return transform(-pivot) * Matrix::rotation(rotation) * transform(pivot);
}

Matrix Matrix::scale(const long double &x, const long double &y, const long double &z)
{
    Matrix result = Matrix(/*4, 4, */true);
    
    result.m[0][0] = x;
    result.m[1][1] = y;
    result.m[2][2] = z;
    
    return result;
}

Matrix Matrix::scale(Vec3f &scale)
{
    return Matrix::scale(scale.x, scale.y, scale.z);
}

Matrix Matrix::scale(Vec3f &scale, Vec3f &pivot)
{
    return transform(-pivot) * Matrix::scale(scale) * transform(pivot);
}

//void Matrix::set(const int &i, const int &j, const long double &value)
//{
//    m[i][j] = value;
//}

//long double Matrix::get(const int &i, const int &j)
//{
//    return m[i][j];
//}

//std::vector<long double> &Matrix::operator[](const int i)
//{
//    return m[i];
//}

Matrix Matrix::operator*(const Matrix &a)
{
    Matrix result;//(/*m_rows, a.m_cols*/);
    long double sum;
    
    for (int i = 0; i < 4/*m_rows*/; i++) {
        for (int j = 0; j < 4/*a.m_cols*/; j++) {
            sum = 0.0L;
            
            for (int k = 0; k < 4/*m_cols*/; k++) {
                sum += m[i][k] * a.m[k][j];
            }
            
            result.m[i][j] = sum;
        }
    }
    
    return result;
}

//int Matrix::rows() const
//{
//    return m_rows;
//}

//int Matrix::cols() const
//{
//    return m_cols;
//}
