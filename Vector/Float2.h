/* Creare una classe Float2 che rappresenti un vettore bidimensionale di numeri float.
 * Fare l'overload di tutti gli operatori ( vettore + vettore, vettore + scalare, vettore + scalare,...)
 * implementare anche prodotti scalari/vettoriali/normalizzazione...
 * Testare tutti gli operatori in un main a parte.
 */

#ifndef FLOAT2_H
#define FLOAT2_H

#include <iostream>
using namespace std;

class Float2 {
private:
    float x;
    float y;

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

    float dotProduct(const Float2& point) const;
    Float2 crossProduct() const;

    float l2Norm() const;
    Float2 normalize();

    float getX() const;
    float getY() const;

    void setX(const float& x);
    void setY(const float& y);
};

ostream& operator<<(ostream& stream, const Float2& point);

Float2 operator*(const float& scalar, const Float2& point);

#endif //FLOAT2_H
