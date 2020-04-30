#include <iostream>
#include "Matrix.h"
#include "../Exception/ExceptionNotifier.h"

Matrix::Matrix(unsigned int rows, unsigned int columns, const initializer_list<float>& data) {
   data_ = FloatArray(rows, columns, data);
}

Matrix::Matrix(unsigned int rows, unsigned int columns, float* data) {
   data_ = FloatArray(rows, columns, data);
}

Matrix::Matrix(const Matrix &matrix) {
   data_ = FloatArray(matrix.get_data());
}

Matrix::Matrix(Matrix &&matrix) {
   data_ = FloatArray(move(matrix.get_data()));

   matrix.delete_matrix();
}

Matrix::~Matrix() {
   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      data_[i] = 0;
   }
}

Matrix &Matrix::operator=(const Matrix &matrix) {
   data_ = FloatArray(matrix.get_data());

   return *this;
}

Matrix &Matrix::operator=(Matrix && matrix) {
   data_ = FloatArray(matrix.get_data());

   matrix.delete_matrix();

   return *this;
}

//TODO fix repeated functions
Matrix Matrix::operator+(const Matrix &matrix) noexcept(false) {
   std::unique_ptr<float> newData(new float[get_rows() * get_columns()]);

   if (get_rows() == matrix.get_rows() && get_columns() == matrix.get_columns()) {
      for (int i = 0; i < get_rows() * get_columns(); ++i) {
         newData.get()[i] = data_[i] + matrix.get_data()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(std::to_string(get_rows())).append(", ").append(std::to_string(get_columns())).append(") ")
         .append(" != (").append(std::to_string(matrix.get_rows())).append(", ").append(std::to_string(matrix.get_columns())).append(")\n");
      // (row, columns_) != (matrix.get_rows(), matrix.get_columns()

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(get_rows(), get_columns(), newData.release());
}

Matrix &Matrix::operator+=(const Matrix &matrix) noexcept(false) {
   if (get_rows() == matrix.get_rows() && get_columns() == matrix.get_columns()) {
      for (int i = 0; i < get_rows() * get_columns(); ++i) {
         data_[i] += matrix.get_data()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(std::to_string(get_rows())).append(", ").append(std::to_string(get_columns())).append(") ")
              .append(" != (").append(std::to_string(matrix.get_rows())).append(", ").append(std::to_string(matrix.get_columns())).append(")\n");
      // (row, columns_) != (matrix.get_rows(), matrix.get_columns()

      throw ExceptionNotifier(s.c_str());
   }

   return *this;
}

Matrix Matrix::operator-(const Matrix &matrix) noexcept(false) {
   std::unique_ptr<float> newData(new float[get_rows() * get_columns()]);

   if (get_rows() == matrix.get_rows() && get_columns() == matrix.get_columns()) {
      for (int i = 0; i < get_rows() * get_columns(); ++i) {
         newData.get()[i] = data_[i] - matrix.get_data()[i];
      }
   } else {
      string s = "Exception: dimensions do not correspond.";
      s.append("(").append(std::to_string(get_rows())).append(", ").append(std::to_string(get_columns())).append(") ")
              .append(" != (").append(std::to_string(matrix.get_rows())).append(", ").append(std::to_string(matrix.get_columns())).append(")\n");
      // (row, columns_) != (matrix.get_rows(), matrix.get_columns()

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(get_rows(), get_columns(), newData.release());
}

Matrix &Matrix::operator-=(const Matrix &matrix) noexcept(false) {
   if (get_rows() == matrix.get_rows() && get_columns() == matrix.get_columns()) {
      for (int i = 0; i < get_rows() * get_columns(); ++i) {
         data_[i] -= matrix.get_data()[i];
      }
   } else {
      string s = "Exception COPY_CONSTRUCTOR: dimensions do not correspond. ";
      s.append("(").append(std::to_string(get_rows())).append(", ").append(std::to_string(get_columns())).append(") ")
              .append(" != (").append(std::to_string(matrix.get_rows())).append(", ").append(std::to_string(matrix.get_columns())).append(")\n");
      // (row, columns_) != (matrix.get_rows(), matrix.get_columns()

      throw ExceptionNotifier(s.c_str());
   }

   return *this;
}

Matrix Matrix::operator*(float scalar) {
   unique_ptr<float> newData(new float[get_rows() * get_columns()]);

   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      newData.get()[i] = data_[i] * scalar;
   }

   return Matrix(get_rows(), get_columns(), newData.release());
}

Matrix& Matrix::operator*=(float scalar) {
   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      data_[i] *= scalar;
   }

   return *this;
}

Matrix Matrix::operator*(Matrix &matrix) noexcept(false) {
   std::unique_ptr<float> newData(new float[get_rows() * matrix.get_columns()]);

   if (get_columns() == matrix.get_rows()) {

      for (unsigned int r = 0; r < get_rows(); ++r) {
         for (unsigned int c = 0; c < get_columns(); ++c) {
            for (unsigned int i = 0; i < get_columns(); ++i) {
               newData.get()[r * get_columns() + c] += data_[r * get_columns() + i] * matrix.get_data()[get_columns() * i + c];
            }
         }
      }
   } else {
      string s = "Exception MATRIX_PRODUCT: dimensions do not correspond. ";
      s.append("(").append(std::to_string(get_columns())).append(", ").append(std::to_string(matrix.get_rows())).append(")\n");

      throw ExceptionNotifier(s.c_str());
   }

   return Matrix(get_rows(), matrix.get_columns(), newData.release());
}

Matrix Matrix::transpose(const Matrix &matrix) {
   unique_ptr<float> newData(new float[matrix.get_rows() * matrix.get_columns()]);

   for (int i = 0; i < matrix.get_columns(); ++i) {
      for (int j = 0; j < matrix.get_rows(); ++j) {
         //TODO check here
         newData.get()[i* matrix.get_rows() + j] = matrix.get_data()[j * matrix.get_columns() + i];
      }
   }

   return Matrix(matrix.get_columns(), matrix.get_rows(), newData.release());
}

Matrix Matrix::create_submatrix(const Matrix &matrix, unsigned int rowIndex, unsigned int columnIndex) {
   std::unique_ptr<float> newData(new float[(matrix.get_rows() - 1) * (matrix.get_columns() - 1)]);

   unsigned int index = 0;
   for (int i = 0; i < matrix.get_rows(); ++i) {
      if (i != rowIndex) {
         for (int j = 0; j < matrix.get_columns(); ++j) {
            if (j != columnIndex) {
               newData.get()[index++] = matrix.get_array()[i * matrix.get_columns() + j];
            }
         }
      }
   }

   return Matrix(matrix.get_rows() - 1, matrix.get_columns() - 1, newData.release());
}

FloatVector Matrix::multiply_vector(const FloatVector& vector) const noexcept(false) {
   if (get_columns() == vector.get_size()) {
      FloatVector newData(get_rows(), {});

      for (int i = 0; i < get_rows(); ++i) {
         float value = 0;

         for (int j = 0; j < get_columns(); ++j) {
            value += get_array()[i * get_columns() + j] * vector.get_vector().get()[j];
         }

         newData.get_vector().get()[i] = value;
      }

      return move(newData);
   } else {
      string s = "Exception NO_MATCH_LENGTH: matrix and vector_ do not have correct size_. ";
      s.append("Matrix columns_: ").append(std::to_string(get_columns())).append("!= Vector size_: ")
         .append(std::to_string(vector.get_size())).append("\n");

      throw ExceptionNotifier(s.c_str());
   }
}

void Matrix::delete_matrix() {
   for (int i = 0; i < get_rows() * get_columns(); ++i) {
      data_[i] = 0;
   }
}

std::string Matrix::to_string() const {
   string s;

   for (auto i = 0; i < get_rows(); ++i) {
      s.append("[");

      for (auto j = 0; j < get_columns(); ++j) {
         s.append(std::to_string(get_array()[i*get_columns() + j])).append("\t");
      }

      s.append("]").append("\n");
   }

   return s;
}

