#ifndef FLOATVECT_H
#define FLOATVECT_H

#include <memory>

using namespace std;

struct FloatArray {
private:
   unsigned int rows_;
   unsigned int columns_;
   unique_ptr<float> array_;

public:
   FloatArray(unsigned short dimension, const initializer_list<float>& data);
   FloatArray(unsigned short rows, unsigned short columns, const initializer_list<float>& data);
   FloatArray(unsigned short rows, unsigned short columns, float*& data);
   FloatArray(const FloatArray& floatArray);
   FloatArray(FloatArray&& floatArray);

   ~FloatArray() {
      rows_ = 0;
      columns_ = 0;
   }

   FloatArray& operator=(const FloatArray& floatArray);

   FloatArray& operator=(FloatArray&& floatArray);

   inline const unique_ptr<float>& get_array() const {
      return array_;
   }

   inline unsigned int get_rows() const {
      return rows_;
   }

   inline unsigned int get_columns() const {
      return columns_;
   }

   float& operator[](int i) {
      return array_.get()[i];
   }
};

#endif //FLOATVECT_H
