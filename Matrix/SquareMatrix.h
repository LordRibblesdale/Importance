#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"
#include "FloatArray.h"

class SquareMatrix : public Matrix {
private:
   FloatArray data_ = FloatArray(nullptr, 0);

public:
   SquareMatrix(float* array, unsigned int dimension);
   SquareMatrix(const SquareMatrix& matrix);
   SquareMatrix(SquareMatrix&& matrix);
   ~SquareMatrix();

   void transpose();
   static SquareMatrix transpose(const SquareMatrix& matrix);

   static SquareMatrix create_submatrix(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   float calculate_determinant() const;
   static float calculate_determinant(const SquareMatrix& matrix);
   static float calculate_cofactor(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   void invert();

   static SquareMatrix calculate_inverse(const SquareMatrix& matrix);

   inline unsigned int get_dimension() const {
      return data_.get_rows();
   }
};

#endif //SQUAREMATRIX_H
