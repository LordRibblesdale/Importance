#include "SquareMatrix.h"
#include "memory"
#include <cmath>

SquareMatrix::SquareMatrix(float *array, unsigned int dimension) : Matrix(array, dimension, dimension) {}

SquareMatrix::SquareMatrix(const SquareMatrix &matrix) : Matrix(matrix) {}

SquareMatrix::SquareMatrix(SquareMatrix &&matrix) : Matrix(std::move(matrix)) {}

SquareMatrix::~SquareMatrix() {}

void SquareMatrix::transpose() {
   Matrix transposed = Matrix::transpose(*this);

   //TODO fix "for" calling (more security in modifying matrix values)
   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      get_array()[i] = transposed.get_array()[i];
   }
}

SquareMatrix SquareMatrix::transpose(const SquareMatrix &matrix) {
   Matrix transposed = Matrix::transpose(matrix);

   return SquareMatrix(transposed.get_array(), transposed.get_rows());
}

SquareMatrix SquareMatrix::create_submatrix(const SquareMatrix &matrix, unsigned int rowIndex, unsigned int columnIndex) {
   Matrix subMatrix = Matrix::create_submatrix(matrix, rowIndex, columnIndex);

   return SquareMatrix(subMatrix.get_array(), subMatrix.get_rows());
}

float SquareMatrix::calculate_determinant() const {
   return calculate_determinant(*this);
}

float SquareMatrix::calculate_determinant(const SquareMatrix& matrix) {
   float determinant = 0;
   const float* array = matrix.get_array();

   //TODO optimise here
   //TODO add 0 calculate_determinant check
   switch (matrix.get_dimension()) {
      case 1:
         determinant = array[0];
         break;
      case 2:
         determinant = array[0]*array[3] - (array[1]*array[2]);
         break;
      case 3:
         determinant = (array[0]*array[4]*array[8] + array[1]*array[5]*array[6] + array[2]*array[3]*array[7])
                 - (array[2]*array[4]*array[6] + array[0]*array[5]*array[7] + array[8]*array[3]*array[1]);
         break;
      default: ;
         /*
         bool calculateRowDeterminant = false;

         for (int i = 0; i < matrix.get_rows(); ++i) {
            unsigned int zeroCount = 0;

            for (int j = 0; j < matrix.get_columns(); ++j) {
               if (matrix.get_array()[i*matrix.get_columns()] == 0) {
                  ++zeroCount;
               }
            }
         }
          */

         //TODO change calculation through first row
         //TODO improve performance for callings and power calculation
         for (int i = 0; i < matrix.get_columns(); ++i) {
            determinant += matrix.get_array()[i] * (powf(-1, i)) * calculate_determinant(create_submatrix(matrix, 0, i));
         }
   }

   return determinant;
}

float SquareMatrix::calculate_cofactor(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex) {
   return calculate_determinant(create_submatrix(matrix, rowIndex, columnIndex));
}

void SquareMatrix::invert() {
   SquareMatrix inverse = SquareMatrix::calculate_inverse(*this);

   //TODO fix "for" calling (more security in modifying matrix values)
   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      get_array()[i] = inverse.get_array()[i];
   }
}

SquareMatrix SquareMatrix::calculate_inverse(const SquareMatrix &matrix) {
   unsigned int dimension = matrix.get_dimension();
   float determinant = matrix.calculate_determinant();
   float newData[dimension*dimension];

   if (determinant != 0) {
      float scalar = 1 / determinant;

      for (int i = 0; i < dimension; ++i) {
         for (int j = 0; j < dimension; ++j) {
            newData[i*dimension + j] = scalar * powf(-1, i+j) * calculate_cofactor(matrix, j, i);
         }
      }
   }

   return SquareMatrix(newData, dimension);
}




