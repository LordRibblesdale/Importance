#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include "Matrix/SquareMatrix.h"

unsigned int LENGTH = 19;

int main(int argc, char** argv) {
   std::ifstream file("matrix");

   if (file.is_open())  {
      std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

      std::vector<std::string> names;
      std::unique_ptr<float> vector(new float[(LENGTH)*(LENGTH)]);
      std::unique_ptr<SquareMatrix> matrix(new SquareMatrix(LENGTH, vector.get()));

      int mi = 0;
      int i = 0;

      int index = 0;
      int temporaryIndex = 0;
      while(index < buffer.size()) {
         if (buffer.at(index) == '\n') {
            std::string tmp(buffer.begin() + temporaryIndex, buffer.begin() + index);
            temporaryIndex = index+1;

            if (i == 0) {
               names.push_back(tmp);
            } else {
               float f = std::stof(tmp);

               if (f == 0) {
                  ++mi;
               } else {
                  matrix->getArray()[mi++] = 1.0f/f;
               }
            }

            if (++i == (LENGTH+1)) {
               i = 0;
            }
         }

         ++index;
      }

      file.close();
      buffer.clear();

      //TODO add Richardson-Euler method
      float c = 0.85;
      std::unique_ptr<Matrix> dangling(new Matrix(LENGTH, 1, {}));
      std::unique_ptr<Matrix> personalizationVector(new Matrix(1, LENGTH, {}));
      std::unique_ptr<Matrix> e(new Matrix(LENGTH, 1, {}));

      std::unique_ptr<FloatVector> z_k(new FloatVector(LENGTH, {}));

      for (i = 0; i < matrix->getDimension(); ++i) {
         float sum = 0;

         for (int j = 0; j < matrix->getDimension(); ++j) {
            sum += matrix->getData()->operator[](i*matrix->getDimension() +j);
         }

         if (sum == 0) {
            dangling->getArray()[i] = 1;
         }

         personalizationVector->getArray()[i] = 1.0f/(LENGTH);
         e->getArray()[i] = 1;
         z_k->getVector().get()[i] = 1.0f/(LENGTH);
      }

      Matrix tmp0(std::move((*personalizationVector)*(1-c)));
      Matrix tmp1(std::move(*e * tmp0));
      Matrix tmp2(std::move(Matrix::transpose((*matrix + *dangling*(*personalizationVector))*c)));
      personalizationVector.release();
      e.release();
      matrix.release();
      dangling.release();

      Matrix aMatrix(std::move(tmp1 + tmp2));

      //TODO fix "criterio di arresto"
      int stop = 0;
      while (++stop < 50) {
         *z_k = std::move(aMatrix.multiplyVector(*z_k));
      }

      std::cout << z_k->toString(names) << std::endl << std::endl;

      std::unique_ptr<Matrix> identity(new Matrix(LENGTH, LENGTH, {}));
      FloatVector tmp3(LENGTH, {});

      /*
      //TODO prepare Richardson-Euler
      //TODO fix values here
      for (i = 0; i < LENGTH; ++i) {
         identity->getArray()[i*LENGTH + i] = 1;
         z_k->getVector().get()[i] = 1.0f/(LENGTH);
         tmp3.getVector().get()[i] = tmp0.getArray()[i];
      }

      *identity -= tmp2;
//
      stop = 0;
      while (++stop < 200) {
         *z_k = std::move(identity->multiplyVector(*z_k) + tmp3);
      }
//
      std::cout << z_k->toString(names) << std::endl << std::endl;
       */
   } else {
      std::cout << "SOS";
   }

   return 0;
}