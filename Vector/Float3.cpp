#include <cmath>
#include "Float3.h"
#include "../Matrix/SquareMatrix.h"

Float3::Float3() : FloatVector(3, {0, 0, 0}) {}

Float3::Float3(const float &x, const float &y, const float &z) : FloatVector(3, {x, y, z}) {}

Float3::Float3(const Float3 &point) : FloatVector(3, {point.get_x(), point.get_y(), point.get_z()}) {}

Float3::Float3(Float3 &&point) : FloatVector(3, {point.get_x(), point.get_y(), point.get_z()}) {
   point.set_x(0);
   point.set_y(0);
   point.set_z(0);
}

Float3::~Float3() {}

Float3 &Float3::operator=(const Float3 &point) {
   set_x(point.get_x());
   set_y(point.get_y());
   set_z(point.get_z());

   return *this;
}

Float3 &Float3::operator=(Float3 &&point) {
   set_x(point.get_x());
   set_y(point.get_y());
   set_z(point.get_z());

   point.set_x(0);
   point.set_y(0);
   point.set_z(0);

   return *this;
}

Float3 Float3::operator+(const Float3 &point) {
   return Float3(get_x() + point.get_x(), get_y() + point.get_y(), get_z() + point.get_z());
}

Float3& Float3::operator+=(const Float3 &point) {
   set_x(get_x() + point.get_x());
   set_y(get_y() + point.get_y());
   set_z(get_z() + point.get_z());

   return *this;
}

Float3 Float3::operator-(const Float3 &point) {
   return Float3(get_x() - point.get_x(), get_y() - point.get_y(), get_z() - point.get_z());
}

Float3& Float3::operator-=(const Float3 &point) {
   set_x(get_x() - point.get_x());
   set_y(get_y() - point.get_y());
   set_z(get_z() - point.get_z());

   return *this;
}

Float3 Float3::operator*(const float &scalar) {
   return Float3(scalar * get_x(), scalar * get_y(), scalar * get_z());
}

Float3& Float3::operator*=(const float &scalar) {
   set_x(get_x() * scalar);
   set_y(get_y() * scalar);
   set_z(get_z() * scalar);

   return *this;
}

float Float3::dot_product(const Float3 &point) const {
   return get_x() * point.get_x() + get_y() * point.get_y() + get_z() * point.get_z();
}

Float3 Float3::cross_product(const Float3& point) const {
   return Float3(get_y() * point.get_z() - get_z() * point.get_y(),
                 -(get_x() * point.get_z() - get_z() * point.get_x()),
                 get_x() * point.get_y() - get_y() * point.get_x());
}

float Float3::l2_norm() const {
   return sqrtf(get_x() * get_x() + get_y() * get_y() + get_z() * get_z());
}

Float3 Float3::normalize() {
   float norm = l2_norm();
    if (norm != 0) {
       float n = 1/norm;
       set_x(get_x()*n);
       set_y(get_y()*n);
       set_z(get_z()*n);
    }

    return *this;
}

float Float3::get_x() const {
   return get_vector().get()[0];
}

float Float3::get_y() const {
   return get_vector().get()[1];
}

float Float3::get_z() const {
   return get_vector().get()[2];
}

void Float3::set_x(const float &x) {
   get_vector().get()[0] = x;
}

void Float3::set_y(const float &y) {
   get_vector().get()[1] = y;
}

void Float3::set_z(const float &z) {
   get_vector().get()[2] = z;
}

Float3 Float3::axisXRotateVertex3(const Float3 &vector, const float& angleX) {
   float cosAngle = cosf(angleX);
   float sinAngle = sinf(angleX);
   SquareMatrix rotation(9, {1, 0, 0, 0, cosAngle, -sinAngle, 0, sinAngle, cosAngle});
   FloatVector rotatedVertex(move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 Float3::axisYRotateVertex3(const Float3 &vector, const float& angleY) {
   float cosAngle = cosf(angleY);
   float sinAngle = sinf(angleY);
   SquareMatrix rotation(9, {cosAngle, 0, sinAngle, 0, 1, 0, -sinAngle, 0, cosAngle});
   FloatVector rotatedVertex(move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}

Float3 Float3::axisZRotateVertex3(const Float3 &vector, const float& angleZ) {
   float cosAngle = cosf(angleZ);
   float sinAngle = sinf(angleZ);
   SquareMatrix rotation(9, {cosAngle, -sinAngle, 0, sinAngle, cosAngle, 0, 0, 0, 1});
   FloatVector rotatedVertex(move(rotation.multiply_vector(vector)));

   return Float3(*static_cast<Float3*>(&rotatedVertex));
}