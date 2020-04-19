#include "Matrix.h"
#include "../Exception/ExceptionNotifier.h"
#include <memory>
#include "..\Vector\Float2.h"
#include "..\Vector\Float3.h"
#include "..\Vector\Float4.h"

Matrix::Matrix(float *array, unsigned int rows, unsigned int columns) {
   data = FloatArray(array, rows, columns);
}

Matrix::Matrix(const Matrix &matrix) {
   data = FloatArray(matrix.getData().getArray(), matrix.getRows(), matrix.getColumns());
}

Matrix::Matrix(Matrix &&matrix) {
   data = FloatArray(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   matrix.deleteMatrix();
}

Matrix::~Matrix() {
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      data[i] = 0;
   }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
   data = FloatArray(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   return *this;
}

Matrix &Matrix::operator=(Matrix && matrix) {
   data = FloatArray(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   matrix.deleteMatrix();

   return *this;
}

Matrix Matrix::operator+(const Matrix &matrix) noexcept(false) {
   float newData[getRows()*getColumns()];

   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         newData[i] = data[i] + matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
         .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")\n");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(newData, getRows(), getColumns());
}

Matrix &Matrix::operator+=(const Matrix &matrix) noexcept(false) {
   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         data[i] += matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")\n");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw ExceptionNotifier(s.c_str());
   }

   return *this;
}

Matrix Matrix::operator-(const Matrix &matrix) noexcept(false) {
   float newData[getRows()*getColumns()];

   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         newData[i] = data[i] - matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")\n");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(newData, getRows(), getColumns());
}

Matrix &Matrix::operator-=(const Matrix &matrix) noexcept(false) {
   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         data[i] -= matrix.getData()[i];
      }
   } else {
      string s = "Exception COPY_CONSTRUCTOR: dimensions do not correspond. ";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")\n");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw ExceptionNotifier(s.c_str());
   }

   return *this;
}

Matrix Matrix::operator*(float scalar) {
   float newData[getRows()*getColumns()];

   for (int i = 0; i < getRows()*getColumns(); ++i) {
      newData[i] = data[i]*scalar;
   }

   return Matrix(newData, getRows(), getColumns());
}

Matrix& Matrix::operator*=(float scalar) {
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      data[i] *= scalar;
   }

   return *this;
}

Matrix Matrix::operator*(Matrix &matrix) noexcept(false) {
   float newData[getRows()*matrix.getColumns()];

   if (getColumns() == matrix.getRows()) {

      for (int r = 0; r < getRows(); ++r) {
         for (int c = 0; c < getColumns(); ++c) {
            for (int i = 0; i < getColumns(); ++i) {
               newData[r*getColumns()+c] += data[r*getColumns()+i]*matrix.getData()[getColumns()*i+c];
            }
         }
      }
   } else {
      string s = "Exception MATRIX_PRODUCT: dimensions do not correspond. ";
      s.append("(").append(to_string(getColumns())).append(", ").append(to_string(matrix.getRows())).append(")\n");

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(newData, getRows(), matrix.getColumns());
}

Matrix Matrix::transpose(const Matrix &matrix) {
   float newData[matrix.getRows()*matrix.getColumns()];

   for (int i = 0; i < matrix.getColumns(); ++i) {
      for (int j = 0; j < matrix.getRows(); ++j) {
         //TODO check here
         newData[i*matrix.getRows() + j] = matrix.getData()[j*matrix.getColumns() + i];
      }
   }

   return Matrix(newData, matrix.getColumns(), matrix.getRows());
}

Matrix Matrix::createSubMatrix(const Matrix &matrix, unsigned int rowIndex, unsigned int columnIndex) {
   float newData[(matrix.getRows()-1)*(matrix.getColumns()-1)];

   for (int i = 0; i < matrix.getRows() && i != rowIndex; ++i) {
      for (int j = 0; j < matrix.getColumns() && j != columnIndex; ++j) {
         newData[i*matrix.getColumns() + j] = matrix.getArray()[i*matrix.getColumns() + j];
      }
   }

   return Matrix(newData, matrix.getRows()-1, matrix.getColumns()-1);
}

FloatVector Matrix::multiplyVector(const FloatVector& vector) noexcept(false) {
   if (getColumns() == vector.getSize()) {
      //TODO build code as FloatVector has coordinates vector in array (no casts + reference in FloatN to array)
      if (typeid(vector) == typeid(Float2)) {

      } else if (typeid(vector) == typeid(Float3)) {

      } else if (typeid(vector) == typeid(Float4)) {

      }
   } else {
      string s = "Exception NO_MATCH_LENGTH: matrix and vector do not have correct size. ";
      s.append("Matrix columns: ").append(to_string(getColumns())).append("!= Vector size: ").append(to_string(vector.getSize())).append("\n");

      throw ExceptionNotifier(s.c_str());
   }

   return NULL;
}

void Matrix::deleteMatrix() {
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      data[i] = 0;
   }
}

