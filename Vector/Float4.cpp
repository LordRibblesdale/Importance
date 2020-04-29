#include <cmath>
#include "Float4.h"
#include "../Matrix/SquareMatrix.h"

Float4::Float4() : FloatVector(4, {0, 0, 0, 0}) {}

Float4::Float4(const float &x, const float &y, const float &z, const float &w) : FloatVector(4, {x, y, z, w}) {}

Float4::Float4(const Float4 &point) : FloatVector(4, {point.get_x(), point.get_y(), point.get_z(), point.get_w()}) {}

Float4::Float4(Float4 &&point) : FloatVector(4, {point.get_x(), point.get_y(), point.get_z(), point.get_w()}) {
   point.set_x(0);
   point.set_y(0);
   point.set_z(0);
   point.set_w(0);
}

Float4::~Float4() {}

Float4 &Float4::operator=(const Float4 &point) {
   set_x(point.get_x());
   set_y(point.get_y());
   set_z(point.get_z());
   set_w(point.get_w());

   return *this;
}

Float4 &Float4::operator=(Float4 &&point) {
   set_x(point.get_x());
   set_y(point.get_y());
   set_z(point.get_z());
   set_w(point.get_w());

   point.set_x(0);
   point.set_y(0);
   point.set_z(0);
   point.set_w(0);

   return *this;
}

Float4 Float4::operator+(const Float4 &point) {
   return Float4(get_x() + point.get_x(), get_y() + point.get_y(), get_z() + point.get_z(), get_w() + point.get_w());
}

Float4& Float4::operator+=(const Float4 &point) {
   set_x(get_x() + point.get_x());
   set_y(get_y() + point.get_y());
   set_z(get_z() + point.get_z());
   set_w(get_w() + point.get_w());

   return *this;
}

Float4 Float4::operator-(const Float4 &point) {
   return Float4(get_x() - point.get_x(), get_y() - point.get_y(), get_z() - point.get_z(), get_w() + point.get_w());
}

Float4& Float4::operator-=(const Float4 &point) {
   set_x(get_x() - point.get_x());
   set_y(get_y() - point.get_y());
   set_z(get_z() - point.get_z());
   set_w(get_w() + point.get_w());

   return *this;
}

Float4 Float4::operator*(const float &scalar) {
   return Float4(scalar * get_x(), scalar * get_y(), scalar * get_z(), scalar * get_w());
}

Float4& Float4::operator*=(const float& scalar) {
   set_x(get_x() * scalar);
   set_y(get_y() * scalar);
   set_z(get_z() * scalar);
   set_w(get_w() * scalar);

   return *this;
}

float Float4::dot_product(const Float4 &point) const {
   return get_x() * point.get_x() + get_y() * point.get_y() + get_z() * point.get_z() + get_w() * point.get_w();
}

/*
Float4 Float4::cross_product(const Float4& point) const {
   return Float4(y * point.get_z() - z * point.get_y(),
                 x * point.get_z() - z * point.get_x(),
                 x * point.get_y() - y * point.get_x());
}
 */

float Float4::l2_norm() const {
   return sqrtf(get_x() * get_x() + get_y() * get_y() + get_z() * get_z() + get_w() * get_w());
}

Float4 Float4::normalize() {
   float norm = l2_norm();
   if (norm != 0) {
      float n = 1/norm;
      set_x(get_x()*n);
      set_y(get_y()*n);
      set_z(get_z()*n);
      set_w(get_w()*n);
   }

   return *this;
}

float Float4::get_x() const {
   return get_vector().get()[0];
}

float Float4::get_y() const {
   return get_vector().get()[1];
}

float Float4::get_z() const {
   return get_vector().get()[2];
}

float Float4::get_w() const {
   return get_vector().get()[3];
}

void Float4::set_x(const float &x) {
   get_vector().get()[0] = x;
}

void Float4::set_y(const float &y) {
   get_vector().get()[1] = y;
}

void Float4::set_z(const float &z) {
   get_vector().get()[2] = z;
}

void Float4::set_w(const float &w) {
   get_vector().get()[3] = w;
}

Float4 Float4::quaternionAxisRotateVertex4(const Float4 &vector, const Float3 &direction, const float &angle) {
   float s;
   float cosAngle;
   Float4 newVector;

   /*
   //TODO optimise here (remainder)
   if (direction.l2_norm() != 0 && remainder(angle, 2*M_PI) != 0) {
      cosAngle = cosf(angle*0.5);
      s = 2/sqrtf(direction.get_x()*direction.get_x() + direction.get_y()*direction.get_y() + direction.get_z()*direction.get_z() + cosAngle*cosAngle);

      SquareMatrix quaternionMatrix(9, {1-s*(direction.get_y()*direction.get_y() + direction.get_z()*direction.get_z(),
                                          s*(direction.get_x()*direction.get_y() - cosAngle))})
   }

    */
   return Float4();
}
