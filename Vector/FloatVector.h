#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

#include <memory>

using namespace std;

class FloatVector {
   unique_ptr<float> vector;
   unsigned int size;

public:
   //TODO fix asking size, use directly iterator and counter inside constructor
   FloatVector(unsigned int size, const initializer_list<float>& data) {
      vector = move(unique_ptr<float>(new float[size]));
      FloatVector::size = size;

      auto iterator = data.begin();
      for (int i = 0; i < size; ++i) {
         vector.get()[i] = *iterator;
         ++iterator;
      }
   }

   FloatVector(const FloatVector& floatVector) {
      vector = unique_ptr<float>(new float[floatVector.getSize()]);
      FloatVector::size = floatVector.getSize();

      for (int i = 0; i < size; ++i) {
         vector.get()[i] = floatVector.getVector().get()[i];
      }
   }

   FloatVector(FloatVector&& floatVector) {
      //TODO test const_cast here
      //USED in: Matrix::multiplyVector()
      vector = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatVector.getVector())).release()));
      size = floatVector.getSize();
   }

   ~FloatVector() {
      size = 0;
   }

   //TODO add all operators and functions

   const unsigned int& getSize() const {
      return size;
   }

   const unique_ptr<float>& getVector() const {
      return vector;
   }


};

#endif //FLOATVECTOR_H
