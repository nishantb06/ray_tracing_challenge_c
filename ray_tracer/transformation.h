#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"
# include "tuple.h"

# define EPSILON 0.00001

Matrix* Translation(float x, float y, float z);
Matrix* Scaling(float x, float y, float z);
Matrix* RotationX(float r);
Matrix* RotationY(float r);
Matrix* RotationZ(float r);
Matrix* Shearing(float xy, float xz, float yx, float yz, float zx, float zy);
Matrix* ViewTransform(Tuple from, Tuple to, Tuple up);

Matrix* Translation(float x, float y, float z) {
    Matrix* translation = Matrix_(4, 4);
    translation->data[0][0] = 1;
    translation->data[1][1] = 1;
    translation->data[2][2] = 1;
    translation->data[3][3] = 1;
    translation->data[0][3] = x;
    translation->data[1][3] = y;
    translation->data[2][3] = z;
    return translation;
}

Matrix* Scaling(float x, float y, float z) {
    Matrix* scaling = Matrix_(4, 4);
    scaling->data[0][0] = x;
    scaling->data[1][1] = y;
    scaling->data[2][2] = z;
    scaling->data[3][3] = 1;
    return scaling;
}

Matrix* RotationX(float r)
{
    // r = radians
    Matrix* rotation = Matrix_(4, 4);
    rotation->data[0][0] = 1;
    rotation->data[1][1] = cos(r);
    rotation->data[1][2] = -sin(r);
    rotation->data[2][1] = sin(r);
    rotation->data[2][2] = cos(r);
    rotation->data[3][3] = 1;
    return rotation;
}

Matrix* RotationY(float r)
{
    // r = radians
    Matrix* rotation = Matrix_(4, 4);
    rotation->data[0][0] = cos(r);
    rotation->data[0][2] = sin(r);
    rotation->data[1][1] = 1;
    rotation->data[2][0] = -sin(r);
    rotation->data[2][2] = cos(r);
    rotation->data[3][3] = 1;
    return rotation;
}

Matrix* RotationZ(float r)
{
    // r = radians
    Matrix* rotation = Matrix_(4, 4);
    rotation->data[0][0] = cos(r);
    rotation->data[0][1] = -sin(r);
    rotation->data[1][0] = sin(r);
    rotation->data[1][1] = cos(r);
    rotation->data[2][2] = 1;
    rotation->data[3][3] = 1;
    return rotation;
}

Matrix* Shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    Matrix* shearing = Matrix_(4, 4);
    shearing->data[0][0] = 1;
    shearing->data[0][1] = xy;
    shearing->data[0][2] = xz;
    shearing->data[1][0] = yx;
    shearing->data[1][1] = 1;
    shearing->data[1][2] = yz;
    shearing->data[2][0] = zx;
    shearing->data[2][1] = zy;
    shearing->data[2][2] = 1;
    shearing->data[3][3] = 1;
    return shearing;
}


#endif // TRANSFORMATION_H