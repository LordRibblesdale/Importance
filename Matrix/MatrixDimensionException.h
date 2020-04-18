#ifndef MATRIXDIMENSIONEXCEPTION_H
#define MATRIXDIMENSIONEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class MatrixDimensionException : public exception {
private:
   const char* s;

public:
   MatrixDimensionException(const char *s);

   const char* what() const noexcept override;
};


#endif //MATRIXDIMENSIONEXCEPTION_H
