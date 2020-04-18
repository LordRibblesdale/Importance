#include <cmath>
#include "Float4.h"

Float4::Float4() : x(0), y(0), z(0), w(0) {}

Float4::Float4(const float &x, const float &y, const float &z, const float &w) : x(x), y(y), z(z), w(w) {}

Float4::Float4(const Float4 &point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();
   w = point.getW();
}

Float4::Float4(Float4 &&point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();
   w = point.getW();

   point.setX(0);
   point.setY(0);
   point.setZ(0);
   point.setW(0);
}

Float4::~Float4() {
   x = 0;
   y = 0;
   z = 0;
   w = 0;
}

Float4 &Float4::operator=(const Float4 &point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();
   w = point.getW();

   return *this;
}

Float4 &Float4::operator=(Float4 &&point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();
   w = point.getW();

   point.setX(0);
   point.setY(0);
   point.setZ(0);
   point.setW(0);

   return *this;
}

Float4 Float4::operator+(const Float4 &point) {
   return Float4(x + point.getX(), y + point.getY(), z + point.getZ(), w + point.getW());
}

Float4& Float4::operator+=(const Float4 &point) {
   x += point.getX();
   y += point.getY();
   z += point.getZ();
   w += point.getW();

   return *this;
}

Float4 Float4::operator-(const Float4 &point) {
   return Float4(x - point.getX(), y - point.getY(), z - point.getZ(), w + point.getW());
}

Float4& Float4::operator-=(const Float4 &point) {
   x -= point.getX();
   y -= point.getY();
   z -= point.getZ();
   w += point.getW();

   return *this;
}

Float4 Float4::operator*(const float &scalar) {
   return Float4(scalar*x, scalar*y, scalar*z, scalar*w);
}

Float4& Float4::operator*=(const float& scalar) {
   x *= scalar;
   y *= scalar;
   z *= scalar;
   w *= scalar;

   return *this;
}


float Float4::dotProduct(const Float4 &point) const {
   return x * point.getX() + y * point.getY() + z * point.getZ() + w * point.getW();
}

/*
Float4 Float4::crossProduct(const Float4& point) const {
   return Float4(y * point.getZ() - z * point.getY(),
                 x * point.getZ() - z * point.getX(),
                 x * point.getY() - y * point.getX());
}
 */

float Float4::l2Norm() const {
   return sqrtf(x*x + y*y + z*z + w*w);
}

Float4 Float4::normalize() {
   float norm = l2Norm();
   if (norm != 0) {
      x /= norm;
      y /= norm;
      z /= norm;
      w /= norm;
   }

   return *this;
}

float Float4::getX() const {
   return x;
}

float Float4::getY() const {
   return y;
}

float Float4::getZ() const {
   return z;
}

float Float4::getW() const {
   return w;
}

void Float4::setX(const float &x) {
   Float4::x = x;
}

void Float4::setY(const float &y) {
   Float4::y = y;
}

void Float4::setZ(const float &z) {
   Float4::z = z;
}

void Float4::setW(const float &w) {
   Float4::z = z;
}
