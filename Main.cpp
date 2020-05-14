#include <fstream>
#include <vector>
#include <iostream>
#include "Matrix/SquareMatrix.h"

unsigned int length = 20;

int main(int argc, char** argv) {
   std::ifstream file("D:\\matrix.csv");

   if (file.is_open())  {
      std::cout.precision(7);

      SquareMatrix matrix(length-1, {});

      std::string s((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      s.append("\0");

      std::vector<std::string> names;

      int previousIndex = 0;
      int index = 0;
      int mi = 0;

      while(index < s.length() && index != -1) {
         for (int i = 0; i < length; ++i) {
            index = s.find(',', index+1);

            if (index != -1) {
               if (i == 0) {
                  names.push_back(std::string(&s[previousIndex], &s[index]));
               } else {
                  std::string sub(&s[previousIndex+1], &s[index]);
                  //std::cout << "Index: " + std::to_string(i) + " - Value: " + sub << std::endl;

                  int slashIndex = sub.find('/');
                  float f2 = 0;

                  if (slashIndex != -1) {
                     //std::cout << std::string(&sub[slashIndex+2]) << std::endl;
                     f2 = 1 / std::stof(std::string(&sub[slashIndex + 1]));
                  }

                  std::cout << f2 << std::endl;

                  matrix.getData()[mi++] = f2;
                  std::cout << matrix.getData()[mi] << std::endl;

               }
            } else {
               break;
            }

            previousIndex = index;
         }
      }

      //std::cout << matrix.toString();
   }

   return 0;
}
