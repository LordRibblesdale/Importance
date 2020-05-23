#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

#include <memory>
#include <iostream>
#include <vector>

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
      //USED in: Matrix::multiplyVector()
      vector_ = move(std::unique_ptr<float>((const_cast<std::unique_ptr<float>&>(floatVector.get_vector())).release()));
      size_ = floatVector.get_size();
   }

   ~FloatVector() {
      size_ = 0;
   }

   //TODO add all operators and functions
   FloatVector& operator=(const FloatVector& vector) {
      vector_ = std::unique_ptr<float>(new float[vector.get_size()]);
      FloatVector::size_ = vector.get_size();

      for (int i = 0; i < size_; ++i) {
         vector_.get()[i] = vector.get_vector().get()[i];
      }

      return *this;
   }

   FloatVector& operator=(FloatVector&& vector) {
      //TODO test const_cast here
      //USED in: Matrix::multiplyVector()
      vector_ = move(std::unique_ptr<float>((const_cast<std::unique_ptr<float>&>(vector.get_vector())).release()));
      size_ = vector.get_size();

      return *this;
   }

   FloatVector operator+(const FloatVector& vector) {
      if (size_ == vector.get_size()) {
         for (int i = 0; i < size_; ++i) {
            vector_.get()[i] += vector.get_vector().get()[i];
         }
      } else {
         std::string s = "Exception VECTOR_SUM: dimensions do not correspond. ";
         s.append("(").append(std::to_string(size_)).append(", ").append(std::to_string(vector.get_size())).append(")\n");

         throw (size_);
      }
   }

   FloatVector operator-(const FloatVector& vector) {
      if (size_ == vector.get_size()) {
         for (int i = 0; i < size_; ++i) {
            vector_.get()[i] -= vector.get_vector().get()[i];
         }
      } else {
         std::string s = "Exception VECTOR_SUM: dimensions do not correspond. ";
         s.append("(").append(std::to_string(size_)).append(", ").append(std::to_string(vector.get_size())).append(")\n");

         throw (size_);
      }
   }

   const unsigned int& get_size() const {
      return size_;
   }

   const std::unique_ptr<float>& get_vector() const {
      return vector_;
   }

   std::string to_string() const {
      std::cout.precision(7);
      std::string s;

      for (auto i = 0; i < get_size(); ++i) {
         s.append("[").append(std::to_string(get_vector().get()[i])).append("]\n");
      }

      return s;
   }

   std::string to_string(std::vector<std::string> names) const {
      std::cout.precision(7);
      std::string s;

      for (auto i = 0; i < get_size(); ++i) {
         s.append(names.at(i)).append(" ").append("[").append(std::to_string(get_vector().get()[i])).append("]\n");
      }

      return s;
   }
};

#endif //FLOATVECTOR_H
