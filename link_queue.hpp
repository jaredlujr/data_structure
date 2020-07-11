#ifndef QUEUE_H_
#define QUEUE_H_
#include "queue.hpp"
#endif



/* This is source code for implementation of linked queue, 
  utilize the templated class.
  
  Cyclic queue implementation : linked
  Use single directed linked list saving 
  No head node
  Remarks:
    single element: front ==  rear == [1]
    empty:  front ==  rear == NULL
*/

template <class elemType>
class LinkQueue: public Queue<elemType> {
 public:
  LinkQueue(void) {front_ = NULL; rear_ = NULL;}
  ~LinkQueue();
  bool isEmpty(void) const {return front_ == NULL;}
  elemType &getFront(void) const {return front_->data;}
  void enQueue(const elemType &x);
  elemType deQueue(void);
 private:
  struct Node {
    elemType data;
    Node *next;
    Node(const elemType &x, Node *n=NULL) {data = x; next = n;}
    ~Node(){}
  };
  Node *front_;
  Node *rear_;
};

template <class elemType>
LinkQueue<elemType>::~LinkQueue() {
  Node *p;  // Point at the oldNode and delete its
  while (front_) {
    p = front_;
    front_ = front_->next;
    delete p;
  }
}

template <class elemType>
void LinkQueue<elemType>::enQueue(const elemType &x) {
  if (rear_ == NULL) {
    front_ = new Node(x);
    rear_ = front_;
  } else {
    rear_->next = new Node(x);
    rear_ = rear_->next;
  }
}

template <class elemType>
elemType LinkQueue<elemType>::deQueue(void) {
  elemType x = front_->data;
  Node *tmp = front_;
  front_ = front_->next;
  if (!front_)  rear_ = NULL;
  delete tmp;
  return x;
}

