#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef ERRORS_H_
#define ERRORS_H_
#include "errors.hpp"
#endif


/* abstract class*/
template <class elemType>
class Stack {
 public:
  virtual bool isEmpty(void) const = 0;
  virtual elemType top(void) const = 0;
  virtual void push(const elemType &x) = 0;
  virtual elemType pop(void) = 0;
  virtual ~Stack(){};
};

