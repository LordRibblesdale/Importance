#ifndef FLOAT4_H
#define FLOAT4_H

#include "FloatVector.h"
#include "Float3.h"

class Float4 : public FloatVector {
public:
   Float4();
   Float4(const float& x, const float& y, const float& z, const float& w);
   Float4(const Float4& point);
   Float4(Float4&& point);
   ~Float4();

   Float4& operator=(const Float4& point);
   Float4& operator=(Float4&& point);

   Float4 operator+(const Float4& point);
   Float4 operator-(const Float4& point);
   Float4& operator+=(const Float4& point);
   Float4& operator-=(const Float4& point);

   Float4 operator*(const float& scalar);
   Float4& operator*=(const float& scalar);

   float dot_product(const Float4& point) const;
   //Float4 cross_product(const Float4& point) const;

   float l2_norm() const;
   Float4 normalize();

   float get_x() const;
   float get_y() const;
   float get_z() const;
   float get_w() const;

   void set_x(const float& x);
   void set_y(const float& y);
   void set_z(const float& z);
   void set_w(const float& w);
};

#endif //FLOAT4_H
