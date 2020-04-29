#ifndef FLOAT3_H
#define FLOAT3_H

#include "FloatVector.h"

class Float3 : public FloatVector {
public:
   Float3();
   Float3(const float& x, const float& y, const float& z);
   Float3(const Float3& point);
   Float3(Float3&& point);
   ~Float3();

   Float3& operator=(const Float3& point);
   Float3& operator=(Float3&& point);

   Float3 operator+(const Float3& point);
   Float3 operator-(const Float3& point);
   Float3& operator+=(const Float3& point);
   Float3& operator-=(const Float3& point);

   Float3 operator*(const float& scalar);
   Float3& operator*=(const float& scalar);

   float dot_product(const Float3& point) const;
   Float3 cross_product(const Float3& point) const;

   float l2_norm() const;
   Float3 normalize();

   float get_x() const;
   float get_y() const;
   float get_z() const;

   void set_x(const float& x);
   void set_y(const float& y);
   void set_z(const float& z);

   // Rotation functions
   static Float3 axisXRotateVertex3(const Float3& vector, const float& angleX);

   static Float3 axisYRotateVertex3(const Float3& vector, const float& angleY);

   static Float3 axisZRotateVertex3(const Float3& vector, const float& angleZ);
};

#endif //FLOAT3_H
