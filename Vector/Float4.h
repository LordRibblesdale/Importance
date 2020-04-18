//
// Created by Green on 17/04/2020.
//

#ifndef FLOAT4_H
#define FLOAT4_H


class Float4 {
private:
   float x;
   float y;
   float z;
   float w;

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

   float dotProduct(const Float4& point) const;
   Float4 crossProduct(const Float4& point) const;

   float l2Norm() const;
   Float4 normalize();

   float getX() const;
   float getY() const;
   float getZ() const;
   float getW() const;

   void setX(const float& x);
   void setY(const float& y);
   void setZ(const float& z);
   void setW(const float& w);
};


#endif //FLOAT4_H
