//
// Created by Green on 17/04/2020.
//

#include <cmath>
#include "Float3.h"

Float3::Float3() : x(0), y(0), z(0) {}

Float3::Float3(const float &x, const float &y, const float &z) : x(x), y(y), z(z) {}

Float3::Float3(const Float3 &point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();
}

Float3::Float3(Float3 &&point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();

   point.setX(0);
   point.setY(0);
   point.setZ(0);
}

Float3::~Float3() {
   x = 0;
   y = 0;
   z = 0;
}

Float3 &Float3::operator=(const Float3 &point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();

   return *this;
}

Float3 &Float3::operator=(Float3 &&point) {
   x = point.getX();
   y = point.getY();
   z = point.getZ();

   point.setX(0);
   point.setY(0);
   point.setZ(0);

   return *this;
}

Float3 Float3::operator+(const Float3 &point) {
   return Float3(x + point.getX(), y + point.getY(), z + point.getZ());
}

Float3& Float3::operator+=(const Float3 &point) {
   x += point.getX();
   y += point.getY();
   z += point.getZ();

   return *this;
}

Float3 Float3::operator-(const Float3 &point) {
   return Float3(x - point.getX(), y - point.getY(), z - point.getZ());
}

Float3& Float3::operator-=(const Float3 &point) {
   x -= point.getX();
   y -= point.getY();
   z -= point.getZ();

   return *this;
}

Float3 Float3::operator*(const float &scalar) {
   return Float3(scalar*x, scalar*y, scalar*z);
}

Float3& Float3::operator*=(const float &scalar) {
   x *= scalar;
   y *= scalar;
   z *= scalar;

   return *this;
}

float Float3::dotProduct(const Float3 &point) const {
   return x * point.getX() + y * point.getY() + z * point.getZ();
}

Float3 Float3::crossProduct(const Float3& point) const {
   return Float3(y * point.getZ() - z * point.getY(),
           -(x * point.getZ() - z * point.getX()),
           x * point.getY() - y * point.getX());
}

float Float3::l2Norm() const {
   return sqrtf(x*x + y*y + z*z);
}

Float3 Float3::normalize() {
   float norm = l2Norm();
    if (norm != 0) {
       x /= norm;
       y /= norm;
       z /= norm;
    }

    return *this;
}

float Float3::getX() const {
   return x;
}

float Float3::getY() const {
   return y;
}

float Float3::getZ() const {
   return z;
}

void Float3::setX(const float &x) {
   Float3::x = x;
}

void Float3::setY(const float &y) {
   Float3::y = y;
}

void Float3::setZ(const float &z) {
   Float3::z = z;
}
