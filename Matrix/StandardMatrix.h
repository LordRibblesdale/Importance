#ifndef STANDARDMATRIX_H
#define STANDARDMATRIX_H

#include "../Vector/Float4.h"
#include "SquareMatrix.h"

//TODO implement in-class methods from this header

static Float3 axisXRotateVertex3(const Float3& vector, const float& angleX);

static Float3 axisYRotateVertex3(const Float3& vector, const float& angleY);

static Float3 axisZRotateVertex3(const Float3& vector, const float& angleZ);

static Float4 quaternionAxisRotateVertex4(const Float4& vector, const Float3& direction, const float& angle);

static SquareMatrix scaleTransform(const SquareMatrix& matrix, float scaleX, float scaleY, float scaleZ);



#endif //STANDARDMATRIX_H
