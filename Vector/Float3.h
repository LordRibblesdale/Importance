#ifndef FLOAT3_H
#define FLOAT3_H

#include "FloatVector.h"

class Float3 : public FloatVector {
private:
   float x;
   float y;
   float z;

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

   float dotProduct(const Float3& point) const;
   Float3 crossProduct(const Float3& point) const;

   float l2Norm() const;
   Float3 normalize();

   float getX() const;
   float getY() const;
   float getZ() const;

   void setX(const float& x);
   void setY(const float& y);
   void setZ(const float& z);
};

#endif //FLOAT3_H
