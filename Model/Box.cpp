#include "Box.h"

Box::Box(const Float3 &initialPoint, const Float3 &finalPoint) : initialPoint_(std::move(initialPoint)), finalPoint_(std::move(finalPoint)) {}
