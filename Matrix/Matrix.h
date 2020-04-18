#ifndef MATRIX_H
#define MATRIX_H

#include "FloatVect.h"

class Matrix {
private:
   FloatVect data = FloatVect(nullptr, 0, 0);

public:
   Matrix(float* array, unsigned short rows, unsigned short columns);
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

   //TODO add transposition, inversion

   inline FloatVect getData() const {
      return data;
   }

   inline float* getArray() const {
      return data.getArray();
   }

   inline unsigned short getRows() const {
      return data.getRows();
   }

   inline unsigned short getColumns() const {
      return data.getColumns();
   }

   void deleteMatrix();
};

#endif //MATRIX_H
