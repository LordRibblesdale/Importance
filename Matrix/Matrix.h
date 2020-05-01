#ifndef MATRIX_H
#define MATRIX_H

#include "FloatArray.h"
#include "../Vector/FloatVector.h"

class Matrix {
protected:
   FloatArray data_ = FloatArray(0, 0, {});

public:
   Matrix(unsigned int rows, unsigned int columns, const std::initializer_list<float>& data);
   Matrix(unsigned int rows, unsigned int columns, float* data);
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

   FloatVector multiply_vector(const FloatVector& vector) const;

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

   std::string to_string() const;
};

#endif //MATRIX_H
