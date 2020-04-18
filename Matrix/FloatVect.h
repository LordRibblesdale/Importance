#ifndef FLOATVECT_H
#define FLOATVECT_H

struct FloatVect {
private:
   unsigned short rows;
   unsigned short columns;
   float* array;

public:
   FloatVect(float* data, unsigned short rows, unsigned short columns) : array(data), rows(rows), columns(columns) {}

   inline float * getArray() const {
      return array;
   }

   inline unsigned short getRows() const {
      return rows;
   }

   inline unsigned short getColumns() const {
      return columns;
   }

   float& operator[](int i) {
      return array[i];
   }
};

#endif //FLOATVECT_H
