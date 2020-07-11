#ifndef LIST_H_
#define LIST_H_
#include "list.hpp"
#endif

/* This is source code for implementation of sequential list, 
    utilize the templated class with some member functions */

// sequential list declaration
template <class elemType>
class SeqList: public List<elemType> {
 public:
  SeqList(int initSize=30);
  ~SeqList(){delete [] data_;}
  int length(void) const {return currentLength_;}
  int index(const elemType &x) const;
  elemType &operator[](int i) const;
  void Insert(const elemType &x, int i);
  void Remove(int i);
  void Clear(void) {currentLength_=0;}
  void Traverse(void) const;
 private:
  elemType *data_;
  int currentLength_;
  int maxSize_;
  void DoubleSpace(void);
};

template <class elemType>
SeqList<elemType>::SeqList(int initSize) {
  data_ = new elemType[initSize];
  if (!data_) throw IllegalSize();
  maxSize_ = initSize;
  currentLength_ = 0;
}

template <class elemType>
int SeqList<elemType>::index(const elemType &x) const {
  int id;
  for (id = 0; id < currentLength_; id++) {
    if (data_[id] == x) 
      break;
  }
  if (id == currentLength_) 
    return -1;
  else 
    return id;
}

template <class elemType>
elemType &SeqList<elemType>::operator[](int i) const {
  if (i < 0 || i > currentLength_) throw OutOfBound();
  return data_[i];
}

template <class elemType>
void SeqList<elemType>::DoubleSpace(void) {
  elemType *tmp = new elemType[maxSize_ * 2];
  if (!tmp) throw IllegalSize();
  for (int i = 0; i < currentLength_; i++)
    tmp[i] = data_[i];
  delete [] data_;
  data_ = tmp;
  maxSize_ *= 2;
}

template <class elemType>
void SeqList<elemType>::Insert(const elemType &x, int i) {
  if (i < 0 || i > currentLength_) {
    throw OutOfBound();
    return;
  }
  if (currentLength_ == maxSize_) DoubleSpace();
  // shift
  for (int j = currentLength_; j > i; j--)
    data_[j] = data_[j-1];

  data_[i] = x;
  currentLength_++;
}

template <class elemType>
void SeqList<elemType>::Remove(int i) {
  if (i < 0 || i > currentLength_) {
    throw OutOfBound();
    return;
  }
  for (int j = i; j < currentLength_; j++)
    data_[j] = data_[j+1];
  currentLength_--;
}

template <class elemType>
void SeqList<elemType>::Traverse(void) const {
  for (int i = 0; i < currentLength_; i++)
    std::cout << data_[i];
  std::cout << std::endl;
}


