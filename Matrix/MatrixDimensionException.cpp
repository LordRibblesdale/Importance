#include "MatrixDimensionException.h"

MatrixDimensionException::MatrixDimensionException(const char *s) {
   MatrixDimensionException::s = s;
}

const char *MatrixDimensionException::what() const noexcept {
   return s;
}
