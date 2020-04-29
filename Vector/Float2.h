/* Creare una classe Float2 che rappresenti un vettore bidimensionale di numeri float.
 * Fare l'overload di tutti gli operatori ( vettore + vettore, vettore + scalare, vettore + scalare,...)
 * implementare anche prodotti scalari/vettoriali/normalizzazione...
 * Testare tutti gli operatori in un main a parte.
 */

#ifndef FLOAT2_H
#define FLOAT2_H

#include <iostream>
#include "FloatVector.h"

using namespace std;

class Float2 : public FloatVector {
public:
    Float2();
    Float2(const float& x, const float& y);
    Float2(const Float2& point);
    Float2(Float2&& point);
    ~Float2();

    Float2& operator=(const Float2& point);
    Float2& operator=(Float2&& point);

    Float2 operator+(const Float2& point);
    Float2 operator-(const Float2& point);

   Float2& operator+=(const Float2& point);
   Float2& operator-=(const Float2& point);

    Float2 operator*(const float& scalar);
    Float2& operator*=(const float& scalar);

    float dot_product(const Float2& point) const;
    Float2 cross_product() const;

    float l2_norm() const;
    Float2 normalize();

    float get_x() const;
    float get_y() const;

    void set_x(const float& x);
    void set_y(const float& y);

    //Rotation functions
    static Float2 axisRotateVertex2(const Float2& vector, const float& angle);
};

ostream& operator<<(ostream& stream, const Float2& point);

Float2 operator*(const float& scalar, const Float2& point);

#endif //FLOAT2_H
