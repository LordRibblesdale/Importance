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
      std::unique_ptr<float> vector(new float[(LENGTH)*(LENGTH)] {0});
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
      personalizationVector.reset();
      e.reset();

      Matrix aMatrix(std::move(tmp1 + tmp2));

      // Sapendo che per teorema matematico la successione è convergente, effettuo tot step per le cifre significative
      int stop = 0;
      while (++stop < 50) {
         *z_k = std::move(aMatrix.multiplyVector(*z_k));
      }

      std::cout << z_k->toString(names) << std::endl << std::endl;


      //TODO prepare Richardson-Euler

      // Matrix I
      std::unique_ptr<Matrix> identity(new Matrix(LENGTH, LENGTH, {}));
      std::unique_ptr<Matrix> identity2(new Matrix(LENGTH, LENGTH, {}));
      FloatVector tmp3(LENGTH, {});
      Matrix b(std::move(Matrix::transpose(tmp0)));

      matrix.reset();
      dangling.reset();

      for (i = 0; i < LENGTH; ++i) {
         identity->getArray()[i*LENGTH + i] = 1;
         identity2->getArray()[i*LENGTH + i] = 1;
         tmp3.getVector().get()[i] = tmp0.getArray()[i];
      }

      // (I - c*(Tr(G) + d v^T)^T)
      *identity -= tmp2;

      float w = 1;

      /*
      for (i = 0; i < LENGTH; ++i) {
         // Using matrix trace as w in (0, 2/lamda_max(I - c*(Tr(G) + d v^T)^T))
         w += identity->getArray()[i*LENGTH + i];
      }
       */

      *identity2 -= *identity*w;

      stop = 0;
      while (++stop < 100) {
         // x_k+1 = (I - wA)x_k + wb)
         *z_k = std::move(identity2->multiplyVector(*z_k) + w*tmp3);
      }

      std::cout << z_k->toString(names) << std::endl << std::endl;
   } else {
      std::cout << "SOS";
   }

   return 0;
}