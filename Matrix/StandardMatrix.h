#ifndef STANDARDMATRIX_H
#define STANDARDMATRIX_H

#include "../Vector/Float4.h"
#include "SquareMatrix.h"
#include <cmath>

//TODO implement in-class methods from this header

Float3 axisXRotateVertex3(const Float3 &vector, const float& angleX) {
   float cosAngle = cosf(angleX);
   float sinAngle = sinf(angleX);
   SquareMatrix rotation(3, {1, 0, 0, 0, cosAngle, -sinAngle, 0, sinAngle, cosAngle});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 axisYRotateVertex3(const Float3 &vector, const float& angleY) {
   float cosAngle = cosf(angleY);
   float sinAngle = sinf(angleY);
   SquareMatrix rotation(3, {cosAngle, 0, sinAngle, 0, 1, 0, -sinAngle, 0, cosAngle});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 axisZRotateVertex3(const Float3 &vector, const float& angleZ) {
   float cosAngle = cosf(angleZ);
   float sinAngle = sinf(angleZ);
   SquareMatrix rotation(3, {cosAngle, -sinAngle, 0, sinAngle, cosAngle, 0, 0, 0, 1});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float4 quaternionAxisRotateVertex4(const Float4 &vector, Float4 &direction, const float &angle) {
   Float4 newVector;

   //TODO optimise here (remainder function)
   if (direction.l2_norm() != 0 && remainder(angle, 2*M_PI) != 0) {
      float sin = sinf(angle*0.5);
      float q1 = direction.get_x()*sin;
      float q2 = direction.get_y()*sin;
      float q3 = direction.get_z()*sin;
      float q4 = direction.get_w()*cosf(angle*0.5);
      //TODO check division here
      float s = 2/(q1*q1 + q2*q2 + q3*q3 + q4*q4);

      SquareMatrix quaternionMatrix(4, {1-s*(q2*q2 + q3*q3),   s*(q1*q2 - q4*q3),   s*(q1*q3 + q4*q2),   0,
                                          s*(q1*q2 + q4*q3),   1-s*(q1*q1 + q3*q3), s*(q2*q3 - q4*q1),   0,
                                          s*(q1*q3 - q4*q2),   s*(q2*q3 + q4*q1),   1-s*(q1*q1 + q2*q2), 0,
                                          0,                   0,                   0,                   1});

      FloatVector fv(quaternionMatrix.multiply_vector(vector));
      newVector = std::move(*static_cast<Float4*>(&fv));
   }

   return newVector;
}

SquareMatrix scaleTransform(const SquareMatrix &matrix, float scaleX, float scaleY, float scaleZ) {
   std::unique_ptr<float> newData(new float[matrix.get_dimension()*matrix.get_dimension()]);

   newData.get()[0] *= scaleX;
   newData.get()[matrix.get_dimension()] *= scaleY;
   newData.get()[matrix.get_dimension()*2] *= scaleZ;

   return SquareMatrix(matrix.get_dimension(), newData.release());
}


static float degree2Radiants(float degree) {
   float inv = 1.0/180;

   return degree * inv * M_PI;
}

static float radiants2Degree(float radiants) {
   float inv = 1.0/M_PI;

   return radiants * 180 * inv;
}

#endif //STANDARDMATRIX_H
