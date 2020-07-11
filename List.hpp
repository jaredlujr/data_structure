#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef ERRORS_H_
#define ERRORS_H_
#include "errors.hpp"
#endif



/* BASE CLASS where virtual functions are defined*/
template <class elemType>
class List {
 public:
  // basic operations of arbitrary list implementation
  virtual int length(void) const = 0; //get the length of list, read-only
  virtual int index(const elemType &x) const = 0; // get the first index of specific element, read-only
  virtual elemType &operator[](int i) const = 0; // same as operator [], read-only
  virtual void Insert(const elemType &x, int i) = 0; //insert new element=x at index=i
  virtual void Remove(int i) = 0; //remove the element present with index=i
  virtual void Clear(void) = 0; // setting the length into zero; THIS IS NOT DELETE.
  virtual void Traverse(void) const = 0; //traverse the whole list, read-only
  virtual ~List(){};
};
