#include <limits>
#include "Ray.h"

Ray::Ray(Float3 &origin, Float3 &direction) : origin_(std::move(origin)), direction_(std::move(direction)) {}

const bool Ray::isIntersecting(const Box &box) {
   float tNear = std::numeric_limits<float>::min();
   float tFar = std::numeric_limits<float>::max();

   for (int i = 0; i < 3; ++i) {
      float inverseDirection = 1/direction_.get_vector().get()[i];
      float t1 = -(box.getInitialPoint().get_vector().get()[i] - origin_.get_vector().get()[i])*inverseDirection;
      float t2 = -(box.getFinalPoint().get_vector().get()[i] - origin_.get_vector().get()[i])*inverseDirection;

      if (t1 > t2) {
         std::swap(t1, t2);
      }

      if (t1 > tNear) {
         tNear = t1;
      }

      if (t2 < tFar) {
         tFar = t2;
      }

      if (tNear > tFar) {
         return false;
      }

      if (tFar < 0) {
         return false;
      }
   }

   return true;
}
