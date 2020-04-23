#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

#include <memory>

struct FloatVector {
   std::unique_ptr<float> vector_;
   unsigned int size_;

public:
   //TODO fix different sizes: data and size
   FloatVector(unsigned int size, const std::initializer_list<float>& data) {
      vector_ = move(std::unique_ptr<float>(new float[size]));
      FloatVector::size_ = size;

      auto iterator = data.begin();
      for (int i = 0; i < size; ++i) {
         vector_.get()[i] = *iterator;
         ++iterator;
      }
   }

   FloatVector(const FloatVector& floatVector) {
      vector_ = std::unique_ptr<float>(new float[floatVector.get_size()]);
      FloatVector::size_ = floatVector.get_size();

      for (int i = 0; i < size_; ++i) {
         vector_.get()[i] = floatVector.get_vector().get()[i];
      }
   }

   FloatVector(FloatVector&& floatVector) {
      //TODO test const_cast here
      //USED in: Matrix::multiply_vector()
      vector_ = move(std::unique_ptr<float>((const_cast<std::unique_ptr<float>&>(floatVector.get_vector())).release()));
      size_ = floatVector.get_size();
   }

   ~FloatVector() {
      size_ = 0;
   }

   //TODO add all operators and functions

   const unsigned int& get_size() const {
      return size_;
   }

   const std::unique_ptr<float>& get_vector() const {
      return vector_;
   }

   std::string to_string() const {
      std::string s;

      for (auto i = 0; i < get_size(); ++i) {
         s.append("[").append(std::to_string(get_vector().get()[i])).append("]\n");
      }

      return s;
   }
};

#endif //FLOATVECTOR_H
