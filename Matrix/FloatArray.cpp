#include "FloatArray.h"

FloatArray::FloatArray(unsigned short rows, unsigned short columns, const std::initializer_list<float> &data) : rows_(rows), columns_(columns) {
   array_ = move(std::unique_ptr<float>(new float[rows*columns]));
   rows_ = rows;
   columns_ = columns;

   auto iterator = data.begin();
   for (int i = 0; i < rows_*columns_; ++i) {
      array_.get()[i] = *iterator;
      ++iterator;
   }
}

FloatArray::FloatArray(unsigned short dimension, const std::initializer_list<float> &data) : FloatArray(dimension, dimension, data) {}

FloatArray::FloatArray(unsigned short rows, unsigned short columns, float*& data) {
   array_ = move(std::unique_ptr<float>(data));
   rows_ = rows;
   columns_ = columns;
}

FloatArray::FloatArray(const FloatArray &floatArray) {
   array_ = std::unique_ptr<float>(new float[floatArray.get_rows() * floatArray.get_columns()]);
   FloatArray::rows_ = floatArray.get_rows();
   FloatArray::columns_ = floatArray.get_columns();

   for (int i = 0; i < rows_ * columns_; ++i) {
      array_.get()[i] = floatArray.get_array().get()[i];
   }
}

FloatArray::FloatArray(FloatArray &&floatArray) {
   //TODO test const_cast here
   array_ = move(std::unique_ptr<float>((const_cast<std::unique_ptr<float>&>(floatArray.get_array())).release()));
   rows_ = floatArray.get_rows();
   columns_ = floatArray.get_columns();

   //TODO check implicit destructor
}

FloatArray &FloatArray::operator=(const FloatArray &floatArray) {
   array_ = std::unique_ptr<float>(new float[floatArray.get_rows() * floatArray.get_columns()]);
   FloatArray::rows_ = floatArray.get_rows();
   FloatArray::columns_ = floatArray.get_columns();

   for (int i = 0; i < rows_ * columns_; ++i) {
      array_.get()[i] = floatArray.get_array().get()[i];
   }

   return *this;
}

FloatArray &FloatArray::operator=(FloatArray &&floatArray) {
   //TODO test const_cast here
   array_ = move(std::unique_ptr<float>((const_cast<std::unique_ptr<float>&>(floatArray.get_array())).release()));
   rows_ = floatArray.get_rows();
   columns_ = floatArray.get_columns();

   //TODO check implicit destructor

   return *this;
}
