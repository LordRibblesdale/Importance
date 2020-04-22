#include "FloatArray.h"

FloatArray::FloatArray(const FloatArray &floatArray) {
   array = unique_ptr<float>(new float[floatArray.get_rows() * floatArray.get_columns()]);
   FloatArray::rows = floatArray.get_rows();
   FloatArray::columns = floatArray.get_columns();

   for (int i = 0; i < rows*columns; ++i) {
      array.get()[i] = floatArray.get_array().get()[i];
   }
}

FloatArray::FloatArray(FloatArray &&floatArray) {
   //TODO test const_cast here
   array = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatArray.get_array())).release()));
   rows = floatArray.get_rows();
   columns = floatArray.get_columns();

   //TODO check implicit destructor
}

FloatArray &FloatArray::operator=(const FloatArray &floatArray) {
   array = unique_ptr<float>(new float[floatArray.get_rows() * floatArray.get_columns()]);
   FloatArray::rows = floatArray.get_rows();
   FloatArray::columns = floatArray.get_columns();

   for (int i = 0; i < rows*columns; ++i) {
      array.get()[i] = floatArray.get_array().get()[i];
   }

   return *this;
}

FloatArray &FloatArray::operator=(FloatArray &&floatArray) {
   //TODO test const_cast here
   array = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatArray.get_array())).release()));
   rows = floatArray.get_rows();
   columns = floatArray.get_columns();

   //TODO check implicit destructor

   return *this;
}


