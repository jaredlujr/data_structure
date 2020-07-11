#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef ERRORS_H_
#define ERRORS_H_
#include "errors.hpp"
#endif

template <class TypeOfVer, class TypeOfEdge>
class Graph {
 public:
  virtual void Insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0;
  virtual void Remove(TypeOfVer x, TypeOfVer y) = 0;
  virtual bool Exist(TypeOfVer x, TypeOfVer y) const = 0;
  int numOfVer(void) const {return numVers_;}
  int numOfEdge(void) const {return numEdges_;}
 protected:
  int numVers_;
  int numEdges_;
};