
#ifndef FLOATVECTOR_H
#define FLOATVECTOR_H

//#include <memory>

//using namespace std;

class FloatVector {
   //unique_ptr<float> vector;
   unsigned int size;

public:
   FloatVector(unsigned int size/*, initializer_list<float> */) {
      //vector = unique_ptr<float>(new float[size]);

      FloatVector::size = size;
   }

   const unsigned int& getSize() const {
      return size;
   }

   /*
   const unique_ptr<float>& getVector() const {
      return vector;
   }
    */
};

#endif //FLOATVECTOR_H
