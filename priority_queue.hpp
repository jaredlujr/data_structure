#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef ERRORS_H_
#define ERRORS_H_
#include "errors.hpp"
#endif

/* 
    leftchild    = (i<<1); 
    rightchild   = (i<<1)+1; 
    parent       = i>>1;
*/
#define LEFT(i)     ( (i << 1) )
#define RIGHT(i)    ( (i << 1) + 1)
#define PARENT(i)   ( i >> 1 )


/* 
Priority Queue/ MinHeap class: 
  - The minimal element is on the root(array[1]);
  - The last leaf node is array[currentSize]
  - The last non-leaf node is array[PARENT(currentSize)]
  - Any subtree is also MinHeap
  - The partial order can be re-defined
*/
template <class elemType>
class PriorityQueue {
 public:
  PriorityQueue(int capacity=100) {
    data_ = new elemType[capacity];
    if (!data_) throw IllegalSize();
    maxSize_ = capacity;
    currentLength_ = 0;
  }
  // Build from Sequential List
  PriorityQueue(const elemType *array, int size);
  ~PriorityQueue(){delete [] data_;}
  virtual bool isEmpty(void) const {return currentLength_ == 0;}
  // Index(root) == 1.  0 storing nothing
  virtual elemType getTop(void) const {return data_[1];}
  virtual void enQueue(const elemType &x);
  elemType deQueue(void);
 private:
  elemType *data_;
  int maxSize_;
  int currentLength_;
  virtual void DoubleSpace(void);
  virtual void Build(void);
  virtual void PercolateDown(int hole);
};


template <class elemType>
void PriorityQueue<elemType>::DoubleSpace(void) {
  elemType *tmp = new elemType[maxSize_ * 2];
  if (!tmp) throw IllegalSize();
  for (int i = 0; i < currentLength_; i++)
    tmp[i+1] = data_[i+1];
  delete [] data_;
  data_ = tmp;
  maxSize_ *= 2;
}

template <class elemType>
void PriorityQueue<elemType>::PercolateDown(int hole) {
  int child;
  elemType x = data_[hole];
  // Find the proper position
  for (; LEFT(hole) <= currentLength_; hole = child) {
    child = LEFT(hole);
    if (LEFT(hole) != currentLength_ && data_[RIGHT(hole)] < data_[LEFT(hole)]) 
      child = RIGHT(hole);  // Get the smallest
    if (data_[child] < x)
      data_[hole] = data_[child];
    else
      break;
  }
  data_[hole] = x;
}

template <class elemType>
void PriorityQueue<elemType>::enQueue(const elemType &x) {
  if (currentLength_ == maxSize_ - 1) DoubleSpace();
  /* Below codes to do percolating Up
     Add another position, and list length++ */
  int hole = ++currentLength_;
  for (; hole > 1 && x < data_[PARENT(hole)]; hole = PARENT(hole))
    data_[hole] = data_[PARENT(hole)];
  data_[hole] = x;
}

template <class elemType>
elemType PriorityQueue<elemType>::deQueue(void) {
  elemType min = data_[1];
  data_[1] = data_[currentLength_--];
  PercolateDown(1);
  return min;
}

template <class elemType>
void PriorityQueue<elemType>::Build(void) {
  for (int i = PARENT(currentLength_); i > 0; i--)
    PercolateDown(i);
}

template <class elemType>
PriorityQueue<elemType>::PriorityQueue(const elemType *array, int size)
: maxSize_(size+10), currentLength_(size) {
  data_ = new elemType[maxSize_];
  if (!data_) throw IllegalSize();
  for (int i = 0; i < size; i++) data_[i+1] = array[i];
  Build();
}


/*  #######################################################################
  Indexing heap as follows: (All from [1]) 
      Table1: Natural index [1,2,..,n], n elements <int>, * mark the 'position' of heap * 
      Table2: Data table [d1,...,dn], n elements <T>,  * pos -> data * 
      Table3: Index table [i1,...,in], n elements <int>, * pos -> rank *
      Table4: Reverse table [r1,..,rn], n elements <int>, * rank -> pos *
    #######################################################################
*/
template <class elemType>
class IndexHeap: public PriorityQueue<elemType> {
 public:
  elemType *data_;
  int *index_;
  int *query_;
  int maxSize_;
  int currentLength_;
  void DoubleSpace(void);
  void Build(void);
  void PercolateDown(int hole);
 private:
  IndexHeap(int capacity=100);
  IndexHeap(const elemType *array, int size);
  ~IndexHeap() {delete [] data_; delete [] index_; delete [] query_;}
  bool isEmpty(void) const {return currentLength_ == 0;}
  elemType getTop(void) const {return data_[1];}
  int MinIndex(void) const {return index_[1];}
  void enQueue(const elemType &x);
};

template <class elemType>
void IndexHeap <elemType>::DoubleSpace(void) {
  elemType *tmp  = new elemType[maxSize_ * 2];
  int *tmp_index = new int[maxSize_ * 2];
  int *tmp_query = new int[maxSize_ * 2];
  // Check memory allocation
  if (!tmp)        throw IllegalSize();
  if (!tmp_index)  throw IllegalSize();
  if (!tmp_query)  throw IllegalSize();
  // Assign the primal value
  for(int j = 1; j <= currentLength_; j++) {
    tmp[j] = data_[j];  // root == array[1]
    tmp_index[j] = index_[j];   // index from 0
    tmp_query[j] = query_[j];   // index from 
  }
  delete [] data_;
  delete [] index_;
  delete [] query_;
  data_ = tmp;
  index_ = tmp_index;
  query_ = tmp_query;
  maxSize_ *= 2;
}

template <class elemType>
void IndexHeap<elemType>::PercolateDown(int hole) {
  int child;
  elemType x = data_[hole];
  int pos = hole;
  int pindex = index_[hole];

  for (; LEFT(hole) <= currentLength_; hole = child) {
    child = LEFT(hole);
    if (LEFT(hole) != currentLength_ && data_[RIGHT(hole)] < data_[LEFT(hole)])
      child = RIGHT(hole);
    if (data_[child] < x) {
      data_[hole] = data_[child];
      index_[hole] = index_[child];
      query_[index_[hole]] = hole;
    }
    else {
      break;
    }
  }
  data_[hole] = x;
  index_[hole] = pindex;
  query_[pindex] = pos;
}


template <class elemType>
void IndexHeap<elemType>::enQueue(const elemType &x) {
  if (currentLength_ == maxSize_ - 1)  DoubleSpace();
  int hole = ++currentLength_;

  /* Below codes to do percolating Up */
  for(; hole > 1 && x < data_[PARENT(hole)]; hole = PARENT(hole)) {
    data_[hole] = data_[PARENT(hole)];
    index_[hole] = index_[PARENT(hole)];
    query_[index_[hole]] = hole;
  }
  data_[hole] = x;
  index_[hole] = currentLength_;
  query_[currentLength_] = hole;
}

template <class elemType>
void IndexHeap<elemType>::Build(void) {
  for (int i = PARENT(currentLength_); i > 0; i--)
    PercolateDown(i);
}

template <class elemType>
IndexHeap<elemType>::IndexHeap(const elemType *array, int size) 
: maxSize_(size+10), currentLength_(size) {
  data_ = new elemType[maxSize_];
  if (!data_) throw IllegalSize();

  for (int i = 0; i <= size; i++) {
    data_[i] = array[i-1];
    index_[i] = i;
    query_[i] = i;
  }
  Build();
}