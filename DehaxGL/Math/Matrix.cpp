#include "Matrix.h"

Matrix::Matrix(int rows, int cols, bool identity)
    : m(std::vector<std::vector<long double>>(rows, std::vector<long double>(cols, 0.0L))),
      m_rows(rows), m_cols(cols)
{
    if (rows == cols && identity) {
        for (int i = 0; i < rows; i++) {
            m[i][i] = 1.0L;
        }
    }
}

Matrix Matrix::transform(long double x, long double y, long double z)
{
    Matrix result = Matrix(4, 4, true);
    
    result[3][0] = x;
    result[3][1] = y;
    result[3][2] = z;
    
    return result;
}

Matrix Matrix::transform(Vec3f offset)
{
    return transform(offset.x, offset.y, offset.z);
}

Matrix Matrix::rotationX(long double angle)
{
    Matrix result = Matrix(4, 4, true);
    
    long double cosAngle = cosl(angle);
    long double sinAngle = sinl(angle);
    
    result[1][1] = cosAngle;
    result[1][2] = sinAngle;
    result[2][1] = -sinAngle;
    result[2][2] = cosAngle;
    
    return result;
}

Matrix Matrix::rotationY(long double angle)
{
    Matrix result = Matrix(4, 4, true);
    
    long double cosAngle = cosl(angle);
    long double sinAngle = sinl(angle);
    
    result[0][0] = cosAngle;
    result[0][2] = -sinAngle;
    result[2][0] = sinAngle;
    result[2][2] = cosAngle;
    
    return result;
}

Matrix Matrix::rotationZ(long double angle)
{
    Matrix result = Matrix(4, 4, true);
    
    long double cosAngle = cosl(angle);
    long double sinAngle = sinl(angle);
    
    result[0][0] = cosAngle;
    result[0][1] = sinAngle;
    result[1][0] = -sinAngle;
    result[1][1] = cosAngle;
    
    return result;
}

Matrix Matrix::rotation(long double angleX, long double angleY, long double angleZ)
{
    return rotationX(angleX) * rotationY(angleY) * rotationZ(angleZ);
}

Matrix Matrix::rotation(Vec3f rotation)
{
    return Matrix::rotation(rotation.x, rotation.y, rotation.z);
}

Matrix Matrix::rotation(Vec3f rotation, Vec3f pivot)
{
    return transform(-pivot) * Matrix::rotation(rotation) * transform(pivot);
}

Matrix Matrix::scale(long double x, long double y, long double z)
{
    Matrix result = Matrix(4, 4, true);
    
    result[0][0] = x;
    result[1][1] = y;
    result[2][2] = z;
    
    return result;
}

Matrix Matrix::scale(Vec3f scale)
{
    return Matrix::scale(scale.x, scale.y, scale.z);
}

Matrix Matrix::scale(Vec3f scale, Vec3f pivot)
{
    return transform(-pivot) * Matrix::scale(scale) * transform(pivot);
}

std::vector<long double> &Matrix::operator [](const int i)
{
    return m[i];
}

Matrix Matrix::operator *(const Matrix &a)
{
    Matrix result(m_rows, a.m_cols);
    
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < a.m_cols; j++) {
            result.m[i][j] = 0.0L;
            
            for (int k = 0; k < m_cols; k++) {
                result.m[i][j] += m[i][k] * a.m[k][j];
            }
        }
    }
    
    return result;
}

int Matrix::rows() const
{
    return m_rows;
}

int Matrix::cols() const
{
    return m_cols;
}
