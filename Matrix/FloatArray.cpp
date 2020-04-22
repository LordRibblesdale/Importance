#include "FloatArray.h"

FloatArray::FloatArray(const FloatArray &floatArray) {
   array = unique_ptr<float>(new float[floatArray.getRows()*floatArray.getColumns()]);
   FloatArray::rows = floatArray.getRows();
   FloatArray::columns = floatArray.getColumns();

   for (int i = 0; i < rows*columns; ++i) {
      array.get()[i] = floatArray.getArray().get()[i];
   }
}

FloatArray::FloatArray(FloatArray &&floatArray) {
   //TODO test const_cast here
   array = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatArray.getArray())).release()));
   rows = floatArray.getRows();
   columns = floatArray.getColumns();

   //TODO check implicit destructor
}

FloatArray &FloatArray::operator=(const FloatArray &floatArray) {
   array = unique_ptr<float>(new float[floatArray.getRows()*floatArray.getColumns()]);
   FloatArray::rows = floatArray.getRows();
   FloatArray::columns = floatArray.getColumns();

   for (int i = 0; i < rows*columns; ++i) {
      array.get()[i] = floatArray.getArray().get()[i];
   }

   return *this;
}

FloatArray &FloatArray::operator=(FloatArray &&floatArray) {
   //TODO test const_cast here
   array = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatArray.getArray())).release()));
   rows = floatArray.getRows();
   columns = floatArray.getColumns();

   //TODO check implicit destructor

   return *this;
}


