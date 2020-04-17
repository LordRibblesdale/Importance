#ifndef MATRIX2_H
#define MATRIX2_H

class Matrix2 {
private:
   float data[4];

public:
   Matrix2(float array[4]);
   Matrix2(const Matrix2& matrix);
   Matrix2(Matrix2&& matrix);
   ~Matrix2();

   Matrix2& operator=(const Matrix2& matrix);
   Matrix2& operator=(Matrix2&&);
   Matrix2& operator+(const Matrix2& matrix);
   Matrix2& operator+(Matrix2&& matrix);
   Matrix2& operator*(float scalar);
   Matrix2& operator*(Matrix2& matrix);

   float* getData();  //return [5]
};

#endif //MATRIX_H
