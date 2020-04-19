#ifndef FLOATVECT_H
#define FLOATVECT_H

struct FloatVect {
private:
   unsigned int rows;
   unsigned int columns;
   float* array;

public:
   FloatVect(float* data, unsigned short dimension) : array(data), rows(dimension), columns(dimension) {};

   FloatVect(float* data, unsigned short rows, unsigned short columns) : array(data), rows(rows), columns(columns) {}

   inline float* getArray() const {
      return array;
   }

   inline unsigned int getRows() const {
      return rows;
   }

   inline unsigned int getColumns() const {
      return columns;
   }

   float& operator[](int i) {
      return array[i];
   }
};

#endif //FLOATVECT_H
