#include "Color.h"

Color::Color(float r, float g, float b) : FloatVector(3, {r, g, b}) {}

const float &Color::getRed() const {
   return vector_.get()[0];
}

const float &Color::getGreen() const {
   return vector_.get()[1];
}

const float &Color::getBlue() const {
   return vector_.get()[2];
}

void Color::setRed(const float &red) {
   vector_.get()[0] = red;
}

void Color::setGreen(const float &green) {
   vector_.get()[1] = green;
}

void Color::setBlue(const float &blue) {
   vector_.get()[2] = blue;
}

void Color::clamp() {

}

int Color::toInt8Bit(const float &f) {
   return 255*f;
}

