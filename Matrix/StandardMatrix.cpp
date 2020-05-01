#include "StandardMatrix.h"

#include <cmath>
#include "SquareMatrix.h"

Float3 axisXRotateVertex3(const Float3 &vector, const float& angleX) {
   float cosAngle = cosf(angleX);
   float sinAngle = sinf(angleX);
   SquareMatrix rotation(9, {1, 0, 0, 0, cosAngle, -sinAngle, 0, sinAngle, cosAngle});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 axisYRotateVertex3(const Float3 &vector, const float& angleY) {
   float cosAngle = cosf(angleY);
   float sinAngle = sinf(angleY);
   SquareMatrix rotation(9, {cosAngle, 0, sinAngle, 0, 1, 0, -sinAngle, 0, cosAngle});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 axisZRotateVertex3(const Float3 &vector, const float& angleZ) {
   float cosAngle = cosf(angleZ);
   float sinAngle = sinf(angleZ);
   SquareMatrix rotation(9, {cosAngle, -sinAngle, 0, sinAngle, cosAngle, 0, 0, 0, 1});
   FloatVector rotatedVertex(std::move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float4 quaternionAxisRotateVertex4(const Float4 &vector, const Float3 &direction, const float &angle) {
   Float4 newVector;

   //TODO optimise here (remainder function)
   if (direction.l2_norm() != 0 && remainder(angle, 2*M_PI) != 0) {
      float q1 = direction.get_x();
      float q2 = direction.get_y();
      float q3 = direction.get_z();
      float q4 = cosf(angle*0.5);
      float s = 2/sqrtf(direction.get_x()*direction.get_x() + direction.get_y()*direction.get_y() + direction.get_z()*direction.get_z() + q4*q4);

      SquareMatrix quaternionMatrix(9, {1-s*(q2*q2 + q3*q3), s*(q1*q2 - q4*q3),   s*(q1*q3 + q4*q2),   0,
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

