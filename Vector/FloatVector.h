#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

#include <memory>

using namespace std;

struct FloatVector {
   unique_ptr<float> vector_;
   unsigned int size_;

public:
   //TODO fix asking size_, use directly iterator and counter inside constructor
   FloatVector(unsigned int size, const initializer_list<float>& data) {
      vector_ = move(unique_ptr<float>(new float[size]));
      FloatVector::size_ = size;

      auto iterator = data.begin();
      for (int i = 0; i < size; ++i) {
         vector_.get()[i] = *iterator;
         ++iterator;
      }
   }

   FloatVector(const FloatVector& floatVector) {
      vector_ = unique_ptr<float>(new float[floatVector.get_size()]);
      FloatVector::size_ = floatVector.get_size();

      for (int i = 0; i < size_; ++i) {
         vector_.get()[i] = floatVector.get_vector().get()[i];
      }
   }

   FloatVector(FloatVector&& floatVector) {
      //TODO test const_cast here
      //USED in: Matrix::multiply_vector()
      vector_ = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatVector.get_vector())).release()));
      size_ = floatVector.get_size();
   }

   ~FloatVector() {
      size_ = 0;
   }

   //TODO add all operators and functions

   const unsigned int& get_size() const {
      return size_;
   }

   const unique_ptr<float>& get_vector() const {
      return vector_;
   }
};

#endif //FLOATVECTOR_H
