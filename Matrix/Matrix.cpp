#include "Matrix.h"
#include "MatrixDimensionException.h"

Matrix::Matrix(float *array, unsigned int rows, unsigned int columns) {
   data = FloatVect(array, rows, columns);
}

Matrix::Matrix(const Matrix &matrix) {
   data = FloatVect(matrix.getData().getArray(), matrix.getRows(), matrix.getColumns());
}

Matrix::Matrix(Matrix &&matrix) {
   data = FloatVect(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   matrix.deleteMatrix();
}

Matrix::~Matrix() {
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      data[i] = 0;
   }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
   data = FloatVect(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   return *this;
}

Matrix &Matrix::operator=(Matrix && matrix) {
   data = FloatVect(matrix.getArray(), matrix.getRows(), matrix.getColumns());

   matrix.deleteMatrix();

   return *this;
}

Matrix Matrix::operator+(const Matrix &matrix) {
   float newData[getRows()*getColumns()];

   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         newData[i] = data[i] + matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
         .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw MatrixDimensionException(s.c_str());
   }

   return Matrix(newData, getRows(), getColumns());
}

Matrix &Matrix::operator+=(const Matrix &matrix) {
   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         data[i] += matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw MatrixDimensionException(s.c_str());
   }

   return *this;
}

Matrix Matrix::operator-(const Matrix &matrix) {
   float newData[getRows()*getColumns()];

   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         newData[i] = data[i] - matrix.getData()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw MatrixDimensionException(s.c_str());
   }

   return Matrix(newData, getRows(), getColumns());
}

Matrix &Matrix::operator-=(const Matrix &matrix) {
   if (getRows() == matrix.getRows() && getColumns() == matrix.getColumns()) {
      for (int i = 0; i < getRows()*getColumns(); ++i) {
         data[i] -= matrix.getData()[i];
      }
   } else {
      string s = "Exception COPY_CONSTRUCTOR: dimensions do not correspond. ";
      s.append("(").append(to_string(getRows())).append(", ").append(to_string(getColumns())).append(") ")
              .append(" != (").append(to_string(matrix.getRows())).append(", ").append(to_string(matrix.getColumns())).append(")");
      // (row, columns) != (matrix.getRows(), matrix.getColumns()

      throw MatrixDimensionException(s.c_str());
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

Matrix Matrix::operator*(Matrix &matrix) {
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
      s.append("(").append(to_string(getColumns())).append(", ").append(to_string(matrix.getRows())).append(")");

      throw MatrixDimensionException(s.c_str());
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

void Matrix::deleteMatrix() {
   for (int i = 0; i < getRows()*getColumns(); ++i) {
      data[i] = 0;
   }
}

