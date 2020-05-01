#include <limits>
#include "Ray.h"

Ray::Ray(Float3 &origin, Float3 &direction) : origin_(std::move(origin)), direction_(std::move(direction)) {}

bool Ray::isIntersecting(const Box &box) const {
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

TriangleIntersection& Ray::getTriangleIntersection(const Triangle &triangle) const {
   std::unique_ptr<TriangleIntersection> intersection = std::make_unique<TriangleIntersection>(false, nullptr, nullptr);

   //TODO optimise memory?
   Float3 q(direction_.cross_product(triangle.getPoint2() - triangle.getPoint0()));
   float determinant = q.dot_product(triangle.getPoint1());

   if (determinant != 0 || (determinant > -EPSILON && determinant < EPSILON)) {
      Float3 s(origin_ - triangle.getPoint0());
      float a = 1 / determinant;

      float u = a*(q.dot_product(s));

      if (u >= 0) {
         Float3 r(s.cross_product(triangle.getPoint1() - triangle.getPoint0()));
         float v = a*(r.dot_product(direction_));

         if (v >= 0 && (u+v) <= 1) {
            float t = a*(r.dot_product(triangle.getPoint2() - triangle.getPoint0()));

            intersection = std::make_unique<TriangleIntersection>(true, new Float3(origin_ + t*direction_), new Float3(t, u, v));
         }
       }
   }

   return *intersection.release();
}

const Float3 &Ray::getOrigin() const {
   return origin_;
}

const Float3 &Ray::getDirection() const {
   return direction_;
}
