#ifndef STACK_H_
#define STACK_H_
#include "stack.hpp"
#endif


/* linked stack implementation, for linked stack, complexity = O(1), because all operatirons afre for top */
template <class elemType>
class LinkStack: public Stack <elemType>
{
 public:
  LinkStack(void) {top_ = NULL;}
  ~LinkStack();
  bool isEmpty(void) const {return !top_;}
  elemType top(void) const;
  elemType pop(void);
  void push(const elemType &x);
 private:
  struct Node {
    elemType data;
    Node *next;
    Node(const elemType &x, Node *n=NULL) {data = x; next = n;}
    ~Node(){};
  };
  Node *top_;
};

template <class elemType>
LinkStack<elemType>::~LinkStack() {
  Node *tmp;
  while (top_) {
    tmp = top_;
    top_ = top_->next;
    delete tmp;
  }
}

template <class elemType>
elemType LinkStack<elemType>::top(void) const {
  if (!top_) 
    throw OutOfBound();
  else
    return top_->data;
}

template <class elemType>
elemType LinkStack<elemType>::pop(void) {
  if (!top_) {
    throw OutOfBound();
  } else {
    Node *tmp = top_;
    elemType x = top_->data;
    top_ = top_->next;
    delete tmp;
    return x;
  }
}

template <class elemType>
void LinkStack<elemType>::push(const elemType &x) {
  Node *tmp = new Node(x, top_);
  top_ = tmp;
}