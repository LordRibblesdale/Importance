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

   static Matrix createSubmatrix(const Matrix& matrix, unsigned int rowIndex, unsigned int columnIndex);

   FloatVector multiplyVector(const FloatVector& vector) const;

   inline FloatArray getData() const {
      return data_;
   }

   inline float* getArray() const {
      return data_.getArray().get();
   }

   inline unsigned int getRows() const {
      return data_.getRows();
   }

   inline unsigned int getColumns() const {
      return data_.getColumns();
   }

   void deleteMatrix();

   std::string toString() const;
};

#endif //MATRIX_H
