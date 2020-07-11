#ifndef STACK_H_
#define STACK_H_
#include "stack.hpp"
#endif

/* IMPLEMENTATION of Sequential stack */

template <class elemType>
class SeqStack: public Stack<elemType> {
 public:
  SeqStack(int initSize=10);
  ~SeqStack() {delete [] data_;};
  bool isEmpty(void) const {return top_==-1;}
  elemType top(void) const {
    if (top_ == -1) throw OutOfBound();
    return data_[top_];
  }
  elemType pop(void) {
    if (top_ == -1) throw OutOfBound();
    return data_[top_--];
  }
  void push(const elemType &x) {
    if (top_ == maxSize_ - 1) DoubleSpace();
    data_[++top_] = x;
  }
 
 private:
  elemType *data_;
  int top_;
  int maxSize_;
  void DoubleSpace(void);
};

template <class elemType>
SeqStack<elemType>::SeqStack(int initSize) {
  data_ = new elemType[initSize];
  if (!data_) throw IllegalSize();
  maxSize_ = initSize;
  top_ = -1;
}

template <class elemType>
void SeqStack<elemType>::DoubleSpace(void) {
  elemType *tmp = new elemType[ maxSize_ * 2];
  if (!tmp) throw IllegalSize();
  for (int i = 0; i < maxSize_; i++)
    tmp[i] = data_[i];
  delete [] data_;
  data_ = tmp;
  maxSize_ *= 2;
}

