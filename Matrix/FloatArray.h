#ifndef FLOATVECT_H
#define FLOATVECT_H

#include <memory>

using namespace std;

struct FloatArray {
private:
   unsigned int rows;
   unsigned int columns;
   unique_ptr<float> array;

public:
   FloatArray(float* data, unsigned short dimension) : array(data), rows(dimension), columns(dimension) {};

   FloatArray(float* data, unsigned short rows, unsigned short columns) : array(data), rows(rows), columns(columns) {}

   FloatArray(const FloatArray& floatArray) {
      array = unique_ptr<float>(new float[floatArray.getRows()*floatArray.getColumns()]);
      FloatArray::rows = floatArray.getRows();
      FloatArray::columns = floatArray.getColumns();

      for (int i = 0; i < rows*columns; ++i) {
         array.get()[i] = floatArray.getArray().get()[i];
      }
   }

   FloatArray(FloatArray&& floatArray) {
      //TODO test const_cast here
      array = move(unique_ptr<float>((const_cast<unique_ptr<float>&>(floatArray.getArray())).release()));
      rows = floatArray.getRows();
      columns = floatArray.getColumns();
   }

   ~FloatArray() {
      rows = 0;
      columns = 0;
   }

   inline const unique_ptr<float>& getArray() const {
      return array;
   }

   inline unsigned int getRows() const {
      return rows;
   }

   inline unsigned int getColumns() const {
      return columns;
   }

   float& operator[](int i) {
      return array.get()[i];
   }
};

#endif //FLOATVECT_H
