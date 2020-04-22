#ifndef EXCEPTIONNOTIFIER_H
#define EXCEPTIONNOTIFIER_H

#include <exception>
#include <string>

using namespace std;

class ExceptionNotifier : public exception {
private:
   const char* s_;

public:
   ExceptionNotifier(const char* s) {
      s_ = s;
   }

   const char *what() const noexcept {
      return s_;
   }
};

#endif //EXCEPTIONNOTIFIER_H
