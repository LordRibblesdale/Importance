#ifndef EXCEPTIONNOTIFIER_H
#define EXCEPTIONNOTIFIER_H

#include <exception>
#include <string>

using namespace std;

class ExceptionNotifier : public exception {
private:
   const char* s;

public:
   ExceptionNotifier(const char *s) {
      ExceptionNotifier::s = s;
   }

   const char *what() const noexcept {
      return s;
   }
};

#endif //EXCEPTIONNOTIFIER_H
