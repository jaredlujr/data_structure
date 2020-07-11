#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef ERRORS_H_
#define ERRORS_H_
#include "errors.hpp"
#endif

/*abstract class*/

template <class elemType>
class Queue {
 public:
  virtual bool isEmpty(void) const = 0; 
  virtual void enQueue(const elemType &x) = 0; // enter (rear)
  virtual elemType deQueue(void) = 0;
  virtual elemType &getFront(void) const = 0; // read the head (first in)
  virtual ~Queue(){}; // when parent point at descendant obj, delete is fine
};
