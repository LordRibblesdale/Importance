#ifndef MATRIX_H
#define MATRIX_H

#include "FloatArray.h"
#include "../Vector/FloatVector.h"

class Matrix {
private:
   FloatArray data_ = FloatArray(nullptr, 0, 0);

public:
   Matrix(float* array, unsigned int rows, unsigned int columns);
   Matrix(const Matrix& matrix);
   Matrix(Matrix&& matrix);
   ~Matrix();

   Matrix& operator=(const Matrix& matrix);
   Matrix& operator=(Matrix&& matrix);
   Matrix operator+(const Matrix& matrix);
   Matrix& operator+=(const Matrix& matrix);
   Matrix operator-(const Matrix& matrix);
   Matrix& operator-=(const Matrix& matrix);
   //TODO complete operator functions
   //Matrix& operator+(Matrix&& matrix);
   Matrix operator*(float scalar);
   Matrix& operator*=(float scalar);
   Matrix operator*(Matrix& matrix);

   static Matrix transpose(const Matrix& matrix);

   static Matrix create_submatrix(const Matrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   FloatVector multiply_vector(const FloatVector& vector);

   inline FloatArray get_data() const {
      return data_;
   }

   inline float* get_array() const {
      return data_.get_array().get();
   }

   inline unsigned int get_rows() const {
      return data_.get_rows();
   }

   inline unsigned int get_columns() const {
      return data_.get_columns();
   }

   void delete_matrix();
};

#endif //MATRIX_H
