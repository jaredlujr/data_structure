#ifndef LIST_H_
#define LIST_H_
#include "list.hpp"
#endif

/* This is source code for implementation of linked list, 
    utilize the templated class with some member functions */


// link list declaration
template <class elemType>
class LinkList: public List<elemType> {
  struct Node {
    elemType data;
    Node *next;
    Node(const elemType &x, Node *n=NULL) {data = x; next = n;}
    Node(void): next(NULL) {};
    ~Node(){};
  };
 public:
  LinkList(void) {
    head_ = new Node();
    currentLength_ = 0;
  }
  ~LinkList(){Clear(); delete head_;}
  int length(void) const {return currentLength_;}
  int index(const elemType &x) const;
  elemType &operator[](int i) const;
  void Insert(const elemType &x, int i);
  void Remove(int i);
  void Clear(void);
  void Traverse(void) const;
 private:
  Node *head_;
  int currentLength_; 
};

template <class elemType>
int LinkList<elemType>::index(const elemType &x) const {
  int id = 0;
  Node *p = head_->next;
  while (p) {
    if (p->data == x) return id;
    p = p->next;
    id++;
  }
  return -1;
}

template <class elemType>
elemType &LinkList<elemType>::operator[](int i) const {
  Node *p = head_->next;
  for (int j = 0; j < i; j++) 
    p = p->next;
  return p->data;
}

template <class elemType>
void LinkList<elemType>::Insert(const elemType &x, int i) {
  if (i > currentLength_ || i < 0 ) {throw OutOfBound(); return;}
  Node *p1 = head_;
  Node *p2 = new Node();
  for (int j = 0; j < i; j++) 
    p1 = p1->next;
  p2->data = x;
  p2->next = p1->next;
  p1->next = p2;

  currentLength_++;
}

template <class elemType>
void LinkList<elemType>::Remove(int i) {
  if (i > currentLength_ || i < 0 ) {throw OutOfBound(); return;}
  Node *p1 = head_;
  Node *p2 = new Node();
  for (int j = 0; j < i; j++) 
    p1 = p1->next;
  p2 = (p1->next)->next;
  delete p1->next;
  p1->next = p2;

  currentLength_--;
}

template <class elemType>
void LinkList<elemType>::Clear(void) {
  Node *p1 = head_->next;
  Node *p2;
  head_->next = NULL;
  while (p1) {
    p2 = p1;
    p1 = p1->next;
    delete p2;
  }
}

template <class elemType>
void LinkList<elemType>::Traverse(void) const {
  Node *p = head_->next;
  while (p) {
    std::cout << p->data << " ";
    p = p->next;
  }
  cout << std::endl;
}