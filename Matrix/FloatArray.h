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

   FloatArray(const FloatArray& floatArray);

   FloatArray(FloatArray&& floatArray);

   ~FloatArray() {
      rows = 0;
      columns = 0;
   }

   FloatArray& operator=(const FloatArray& floatArray);

   FloatArray& operator=(FloatArray&& floatArray);

   inline const unique_ptr<float>& get_array() const {
      return array;
   }

   inline unsigned int get_rows() const {
      return rows;
   }

   inline unsigned int get_columns() const {
      return columns;
   }

   float& operator[](int i) {
      return array.get()[i];
   }
};

#endif //FLOATVECT_H
