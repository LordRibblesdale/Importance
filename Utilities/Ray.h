#ifndef RAY_H
#define RAY_H

#include <memory>
#include <utility>

#include "../Vector/Float3.h"
#include "Box.h"

struct Intersection {
private:
   bool hasIntersected_;
   std::unique_ptr<Float3> intersectedPoint_ = nullptr;

public:
   Intersection(bool hasIntersected, Float3* intersectedPoint) : hasIntersected_(hasIntersected), intersectedPoint_(intersectedPoint) {}

   inline bool getHasIntersected() const {
      return hasIntersected_;
   }

   inline const Float3& getIntersectedPoint() const {
      return *intersectedPoint_;
   }
};

class Ray {
   Float3 origin_;
   Float3 direction_;

   Ray(Float3& origin, Float3& direction);

   const bool isIntersecting(const Box& box);
};


#endif //RAY_H
