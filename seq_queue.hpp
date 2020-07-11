#ifndef QUEUE_H_
#define QUEUE_H_
#include "queue.hpp"
#endif


/* This is source code for implementation of sequential queue, 
    utilize the templated class */


/* 
    Cyclic queue implementation 
    Now Q[Maxsize] is the Q[0], front at Q[1]
    we can take the modulo of Maxsize, very easy!
    # ENTER # : rear  := (rear+1)  % Maxsize; Q[rear] = x;
    # Out   # : front := (front+1) % Maxsize
    The elements sequence can "shift" on a loop, expand the loop if necessary

    Some remarks to consider:
    # front is the leader flag but not "first in"
    *front <- Out(dequeue) here <===   [1] <-  [2] <- ... <- *rear <=== append(enqueue) here
    #### flags ####
    # Empty: after pop,    the front shift to rear: front == rear
    # Full:  after enter , the rear is about to shift to front: (rear+1) % Maxsize == front
*/

template <class elemType>
class SeqQueue: public Queue<elemType> {
 public:
  SeqQueue(int initSize=10) {
    data_ = new elemType[initSize];
    maxSize_ = initSize;
    front_ = 0;
    rear_ = 0;
  }
  ~SeqQueue() {delete [] data_;}
  bool isEmpty(void) const {return front_ == rear_;}
  elemType &getFront(void) const {return data_[(front_ + 1) % maxSize_];}
  void enQueue(const elemType &x);
  elemType deQueue(void);
 private:
  elemType *data_;
  int rear_;
  int front_;
  int maxSize_;
  void DoubleSpace(void);
};

template <class elemType>
void SeqQueue<elemType>::DoubleSpace(void) {
  elemType *tmp = new elemType[maxSize_ * 2];
  if (!tmp) throw IllegalSize();
  for (int i = 0; i < maxSize_; i++)
    tmp[i] = data_[(front_ + i) % maxSize_];

  delete [] data_;  
  data_ = tmp;
  
  front_ = 0;
  rear_ = maxSize_ - 1;
  maxSize_ *= 2;
}

template <class elemType>
void SeqQueue<elemType>::enQueue(const elemType &x) {
  if ( (rear_ + 1) % maxSize_ == front_)
    DoubleSpace();
  rear_ = (rear_ + 1) % maxSize_;
  data_[rear_] = x;
}

template <class elemType>
elemType SeqQueue<elemType>::deQueue(void) {
  front_ = (front_ + 1) % maxSize_;
  return data_[front_];
}