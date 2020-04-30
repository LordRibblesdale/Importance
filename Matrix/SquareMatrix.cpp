#include "SquareMatrix.h"
#include "memory"
#include <iostream>

SquareMatrix::SquareMatrix(unsigned int dimension, const initializer_list<float>& data) : Matrix(dimension, dimension, data) {}

SquareMatrix::SquareMatrix(unsigned int dimension, float* array) : Matrix(dimension, dimension, std::move(array)) {}

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

   //TODO check cast
   return SquareMatrix(move(*static_cast<SquareMatrix*>(&transposed)));
}

SquareMatrix SquareMatrix::create_submatrix(const SquareMatrix &matrix, unsigned int rowIndex, unsigned int columnIndex) {
   Matrix subMatrix = Matrix::create_submatrix(matrix, rowIndex, columnIndex);

   return SquareMatrix(move(*static_cast<SquareMatrix*>(&subMatrix)));
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
            determinant += matrix.get_array()[i] * (i % 2 == 0 ? 1 : -1) * calculate_determinant(create_submatrix(matrix, 0, i));
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
   std::unique_ptr<float> newData(new float[dimension*dimension]);

   if (determinant != 0) {
      float scalar = abs(1 / determinant);

      for (unsigned int i = 0; i < dimension; ++i) {
         for (unsigned int j = 0; j < dimension; ++j) {
            newData.get()[i*dimension + j] = scalar * ((i+j) % 2 == 0 ? 1 : -1) * calculate_cofactor(matrix, j, i);
         }
      }
   }

   return SquareMatrix(dimension, newData.release());
}

//TODO create new classes Matrix2, Matrix3 and Matrix4
void SquareMatrix::scaleMatrix(float scaleX, float scaleY, float scaleZ) {
   //TODO automise here
   data_.get_array().get()[0] *= scaleX;
   data_.get_array().get()[get_dimension()] *= scaleY;
   data_.get_array().get()[get_dimension()*2] *= scaleZ;
}




