#include <fstream>
#include <vector>
#include <iostream>
#include <memory>
#include "Matrix/SquareMatrix.h"

unsigned int LENGTH = 20;

int main(int argc, char** argv) {
   std::ifstream file("matrix");

   if (file.is_open())  {
      std::cout.precision(7);

      std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

      std::vector<std::string> names;
      std::shared_ptr<float> vector(new float[(LENGTH-1)*(LENGTH-1)]);
      SquareMatrix matrix(LENGTH-1, vector.get());

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
                  matrix.getArray()[mi++] = 1.0f/f;
               }
            }

            if (++i == LENGTH) {
               i = 0;
            }
         }

         ++index;
      }

      file.close();
      buffer.clear();

      std::cout << matrix.toString() << std::endl;

      /*
      Matrix dangling(LENGTH-1, 1, {});

      for (i = 0; i < matrix.getDimension(); ++i) {
         float sum = 0;

         for (int j = 0; j < matrix.getDimension(); ++j) {
            sum += matrix.getData()[i*matrix.getDimension() +j];
         }

         if (sum == 0) {
            dangling.getArray()[i] = 1;
         }
      }

      //TODO add Richardson-Euler method
      float c = 0.85;

      Matrix personalizationVector(1, LENGTH-1, {});

      for (i = 0; i < personalizationVector.getColumns(); ++i) {
         personalizationVector.getArray()[i] = 1.0f/(LENGTH-1);
      }

      Matrix e(LENGTH-1, 1, {});

      for (i = 0; i < e.getRows(); ++i) {
         e.getArray()[i] = 1;
      }

      Matrix first(matrix + dangling*personalizationVector);

      Matrix second(e*personalizationVector);

      first *= c;
      second *= (1-c);
      first += second;

      SquareMatrix aMatrix(SquareMatrix::transpose(*static_cast<SquareMatrix*>(&first)));

      FloatVector z_k(LENGTH-1, {});
      FloatVector previousZk(LENGTH-1, {});

      //TODO check on personalization vector
      for (i = 0; i < LENGTH-1; ++i) {
         z_k.get_vector().get()[i] = 1.0f/(LENGTH-1);
      }

      /*
      //TODO fix "criterio di arresto"
      while (true) {
         previousZk = z_k;
         z_k = std::move(aMatrix.multiplyVector(z_k));
         std::cout << z_k.to_string() << std::endl << std::endl;
      }
       */

   } else {
      std::cout << "SOS";
   }

   return 0;
}