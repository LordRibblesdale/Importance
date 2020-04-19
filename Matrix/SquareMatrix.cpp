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
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      getArray()[i] = transposed.getArray()[i];
   }
}

SquareMatrix SquareMatrix::transpose(const SquareMatrix &matrix) {
   Matrix transposed = Matrix::transpose(matrix);

   return SquareMatrix(transposed.getArray(), transposed.getRows());
}

SquareMatrix SquareMatrix::createSubMatrix(const SquareMatrix &matrix, unsigned int rowIndex, unsigned int columnIndex) {
   Matrix subMatrix = Matrix::createSubMatrix(matrix, rowIndex, columnIndex);

   return SquareMatrix(subMatrix.getArray(), subMatrix.getRows());
}

float SquareMatrix::calculateDeterminant() const {
   return calculateDeterminant(*this);
}

float SquareMatrix::calculateDeterminant(const SquareMatrix& matrix) {
   float determinant = 0;
   const float* array = matrix.getArray();

   //TODO optimise here
   //TODO add 0 calculateDeterminant check
   switch (matrix.getDimension()) {
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

         for (int i = 0; i < matrix.getRows(); ++i) {
            unsigned int zeroCount = 0;

            for (int j = 0; j < matrix.getColumns(); ++j) {
               if (matrix.getArray()[i*matrix.getColumns()] == 0) {
                  ++zeroCount;
               }
            }
         }
          */

         //TODO change calculation through first row
         //TODO improve performance for callings and power calculation
         for (int i = 0; i < matrix.getColumns(); ++i) {
            determinant += matrix.getArray()[i]*(powf(-1, i))*calculateDeterminant(createSubMatrix(matrix, 0, i));
         }
   }

   return determinant;
}

float SquareMatrix::calculateCofactor(const SquareMatrix& matrix, unsigned int rowIndex, unsigned int columnIndex) {
   return calculateDeterminant(createSubMatrix(matrix, rowIndex, columnIndex));
}

void SquareMatrix::invert() {
   SquareMatrix inverse = SquareMatrix::calculateInverse(*this);

   //TODO fix "for" calling (more security in modifying matrix values)
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      getArray()[i] = inverse.getArray()[i];
   }
}

SquareMatrix SquareMatrix::calculateInverse(const SquareMatrix &matrix) {
   unsigned int dimension = matrix.getDimension();
   float determinant = matrix.calculateDeterminant();
   float newData[dimension*dimension];

   if (determinant != 0) {
      float scalar = 1 / determinant;

      for (int i = 0; i < dimension; ++i) {
         for (int j = 0; j < dimension; ++j) {
            newData[i*dimension + j] = scalar * powf(-1, i+j) * calculateCofactor(matrix, j, i);
         }
      }
   }

   return SquareMatrix(newData, dimension);
}




