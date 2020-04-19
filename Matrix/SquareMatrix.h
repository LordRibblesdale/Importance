#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"
#include "FloatVect.h"

class SquareMatrix : public Matrix {
private:
   FloatVect data = FloatVect(nullptr, 0);

public:
   SquareMatrix(float* array, unsigned int dimension);
   SquareMatrix(const SquareMatrix& matrix);
   SquareMatrix(SquareMatrix&& matrix);
   ~SquareMatrix();

   void transpose();
   static SquareMatrix transpose(const SquareMatrix& matrix);

   static SquareMatrix createSubMatrix(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   float calculateDeterminant() const;
   static float calculateDeterminant(const SquareMatrix& matrix);
   static float calculateCofactor(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   void invert();

   static SquareMatrix calculateInverse(const SquareMatrix& matrix);

   inline unsigned int getDimension() const {
      return data.getRows();
   }
};

#endif //SQUAREMATRIX_H
