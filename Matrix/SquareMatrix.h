#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "Matrix.h"
#include "FloatArray.h"

class SquareMatrix : public Matrix {
public:
   SquareMatrix(unsigned int dimension, const std::initializer_list<float>& data);
   SquareMatrix(unsigned int dimension, float* data);
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

   void scaleMatrix(float scaleX, float scaleY, float scaleZ);

   static SquareMatrix calculate_inverse(const SquareMatrix& matrix);

   inline unsigned int get_dimension() const {
      return data_.get_rows();
   }
};

#endif //SQUAREMATRIX_H
