//
// Created by Green on 19/03/2020.
//

/* Creare una classe Float2 che rappresenti un vettore bidimensionale di numeri float.
 * Fare l'overload di tutti gli operatori ( vettore + vettore, vettore + scalare, vettore + scalare,...)
 * implementare anche prodotti scalari/vettoriali/normalizzazione...
 * Testare tutti gli operatori in un main a parte.
 */

#include <cmath>
#include "Float2.h"
#include "../Matrix/SquareMatrix.h"

Float2::Float2() : FloatVector(2, {0, 0}) {}

Float2::Float2(const float& x, const float& y) : FloatVector(2, {x, y}) {}

Float2::Float2(const Float2 &point) : FloatVector(2, {point.get_x(), point.get_y()}) {}

Float2::Float2(Float2&& point) : FloatVector(2, {point.get_x(), point.get_y()}) {
   point.set_x(0);
   point.set_y(0);
}

Float2::~Float2() {}

//TODO missing "+=" e "-=" operators

Float2& Float2::operator=(const Float2 &point) {
   set_x(point.get_x());
   set_y(point.get_y());

   return *this;
}

Float2& Float2::operator=(Float2&& point) {
   set_x(point.get_x());
   set_y(point.get_y());

   point.set_x(0);
   point.set_y(0);

   return *this;
}

Float2 Float2::operator+(const Float2& point) {
   return Float2(get_x() + point.get_x(), get_y() + point.get_y());
}

Float2 Float2::operator-(const Float2& point) {
   return Float2(get_x() - point.get_x(), get_y() - point.get_y());
}

Float2 &Float2::operator+=(const Float2 &point) {
   set_x(get_x() + point.get_x());
   set_y(get_y() + point.get_y());

   return *this;
}

Float2 &Float2::operator-=(const Float2 &point) {
   set_x(get_x() - point.get_x());
   set_y(get_y() - point.get_y());

   return *this;
}

Float2 Float2::operator*(const float& scalar) {
   return Float2(scalar * get_x(), scalar * get_y());
}

Float2& Float2::operator*=(const float& scalar) {
   set_x(get_x() * scalar);
   set_y(get_y() * scalar);
   return *this;
}

float Float2::dot_product(const Float2& point) const {
   return get_x() * point.get_x() + get_y() * point.get_y();
}

Float2 Float2::cross_product() const {
   return Float2(get_y(), -get_x());
}

float Float2::l2_norm() const {
   return sqrtf(get_x() * get_x() + get_y() * get_y());
}

Float2 Float2::normalize() {
   float norm = l2_norm();

   if (norm != 0) {
      float n = 1/norm;
      set_x(get_x()*n);
      set_y(get_y()*n);
   }

   return *this;
}

float Float2::get_x() const {
   return get_vector().get()[0];
}

float Float2::get_y() const {
   return get_vector().get()[1];
}

void Float2::set_x(const float& x) {
   get_vector().get()[0] = x;
}

void Float2::set_y(const float& y) {
   get_vector().get()[1] = y;
}

Float2 Float2::axisRotateVertex2(const Float2 &vector, const float& angle) {
   float cosAngle = cosf(angle);
   float sinAngle = sinf(angle);
   SquareMatrix rotation(4, {cosAngle, -sinAngle, sinAngle, cosAngle});
   FloatVector rotatedVertex(move(rotation.multiply_vector(vector)));

   return Float2(*static_cast<Float2*>(&rotatedVertex));
}

ostream& operator<<(ostream& stream, const Float2& point) {
   return stream << "Point (" << point.get_x() << ", " << point.get_y() << ")";
}


Float2 operator*(const float& scalar, const Float2& point) {
   return Float2(point.get_x() * scalar, point.get_y() * scalar);
}
