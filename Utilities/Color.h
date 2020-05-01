#ifndef COLOR_H
#define COLOR_H

#include "../Vector/FloatVector.h"

class Color : public FloatVector {
public:
   Color(float r, float g, float b);

   const float& getRed() const;
   const float& getGreen() const;
   const float& getBlue() const;

   void setRed(const float& red);
   void setGreen(const float& green);
   void setBlue(const float& blue);

   void clamp();

   static int toInt8Bit(const float& f);
};

#endif //COLOR_H
