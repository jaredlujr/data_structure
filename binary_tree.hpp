#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#ifndef SEQLIST_H_
#define SEQLIST_H_
#include "seq_list.hpp"
#endif
#ifndef SEQSTACK_H_
#define SEQSTACK_H_
#include "seq_stack.hpp"
#endif
#ifndef SEQQUEUE_H_
#define SEQQUEUE_H_
#include "seq_queue.hpp"
#endif

/* Binary tree pre-statement */
template <class elemtype>
class BinaryTree;

/* [Friend to BinaryTree]Tree Node class*/
template <class elemType>
class Node {
  friend class BinaryTree<elemType>;
 public:
  Node(void){left_ = NULL; right_ = NULL; leftFlag_ = 0; rightFlag_ = 0;}
  Node(const elemType &e, Node *lt = NULL, Node *rt = NULL)
  : data_(e), left_(lt), right_(rt), leftFlag_(0), rightFlag_(0){}
 private:
  elemType data_;
  Node *left_;
  Node *right_;
  int leftFlag_;
  int rightFlag_;
};

/* Binary (linked) list -> Binary Tree */
template <class elemType>
class BinaryTree {
 public:
  BinaryTree(void){root_ = NULL;}
  bool isEmpty(void) const {return root_ == NULL;}
  bool isComplete(void) const;
  Node<elemType> *getRoot(void) const {return root_;}
  int Size(void) const {return Size(root_);}
  int Height(void) const {return Height(root_);}
  /*Create Tree from InStream*/
  void CreateTree(const elemType &sflag);
  void CreateFromRoot(Node<elemType> *r) {root_ = r;}
  void Build(void);
  Node<elemType> *BuildFromPreIn(elemType pre[], int pl, int pr, 
                                 elemType in[], int il, int ir);
  Node<elemType> *BuildFromInPost(elemType in[], int il, int ir, 
                                  elemType post[], int pl, int pr);
  void DelTree(void) {
    if (root_) DelTree(root_);
    root_ = NULL;
  }
  /* 
    Traverse function: in which way output all the elements
    In specific manner with different tools:
    Queue-like: LevelOrder
    Stack-like: Others
  */
  void PreOrder(void) const {PreOrder(root_);}
  void InOrder(void) const {InOrder(root_);}
  void PostOrder(void) const {PostOrder(root_);}
  void LevelOrder(void) const;
  /*Non-recursive version*/
  void PreOrder_nr(void) const;
  void InOrder_nr(void) const;
  void InOrder_nr2(void) const;
  void PostOrder_nr(void) const;
  void PostOrder_nr2(void) const;

 private:
  Node<elemType> *root_;
  elemType stopFlag_;

  /*The size of tree t, recursive*/
  int Size(Node<elemType> *t) const {
    if (!t) return 0;
    return 1 + Size(t->left_) + Size(t->right_);
  }
  /*The height of tree t, recursive*/
  int Height(Node<elemType> *t) const {
    if (!t) return 0;
    int lt = Height(t->left_);
    int rt = Height(t->right_);
    return 1 + (lt>rt?lt:rt);
  }
  /*Delete the tree t, recursive and postorder*/
  void DelTree(Node<elemType> *t) {
    if (t->left_) DelTree(t->left_);
    if (t->right_) DelTree(t->right_);
    delete t;
  }
  /*For recursive implementation of traversal*/
  void PreOrder(Node<elemType> *t) const;
  void InOrder(Node<elemType> *t) const;
  void PostOrder(Node<elemType> *t) const;
};


/* 
    Creating prcess:
        - root creating with data
        - for each added nodes, push its two children or NULL; (only two Nodes regardless of the rest descendants)
    Using Queue:
        - push the newly added Nodes into queue
        - sequentially push the children of Outqueue element
        Example:
        <-[1]<- ... 1{2,3}
        <-[2,3]<-  ... 2{4,5}
        <-[3,4,5]<- ... 3{6,7}
        <-[4,5,6,7]<- ...
*/

template <class elemType>
void BinaryTree<elemType>::CreateTree(const elemType &sflag) {
  SeqQueue<Node<elemType> *> q1;
  elemType e;
  elemType el;
  elemType er;
  Node<elemType> *p;
  Node<elemType> *pl;
  Node<elemType> *pr;
  stopFlag_ = sflag;

  std::cout << "Root:"; 
  cin >> e;
  if (e == stopFlag_) {
    root_ = NULL;
    return;
  }

  p = new Node<elemType>(e);
  root_ = p;
  q1.enQueue(p);

  while (!q1.isEmpty()) {
    p = q1.getFront();
    q1.deQueue();
    std::cout << "Left Child, Right child: (using " << stopFlag_ << "as no child)";
    cin >> el >> er;

    if (el != stopFlag_) {
      pl = new Node<elemType>(el);
      p->left_ = pl;
      q1.enQueue(pl);
    }
    
    if (er != stopFlag_) {
      pr = new Node<elemType>(er);
      p->right_ = pr;
      q1.enQueue(pr);
    }
  }
}

/*
Batch input:
    - N (size of tree)
    for i=1...N
    - Le Qe as the left child and right child of node i
    - 0 as NULL
*/
template <class elemType>
void BinaryTree<elemType>::Build(void) {
  int n;
  int le;
  int re;
  cin >> n;
  
  Node<elemType> *tmp[n];
  int flags[n];
  for (int i = 0; i < n; i++) {
    tmp[i] = new Node<elemType>(i+1);
    flags[i] = 1;
  }

  for(int i = 0; i < n; i++) {
    cin >> le >> re;
    if (le > 0) {
      flags[le - 1] = 0;
      (tmp[i])->left_ = tmp[le - 1];
    }
    if (re > 0) {
      flags[re - 1] = 0;
      (tmp[i]->right_) = tmp[re - 1];
    }
  }
  for (int i = 0; i < n; i++) 
    if (flags[i] == 1) root_ = tmp[i];
}

template <class elemType>
void BinaryTree<elemType>::PreOrder(Node<elemType> *t) const {
  if (!t) return;
  std::cout << t->data_ << " ";
  PreOrder(t->left_);
  PreOrder(t->right_);
}

template <class elemType>
void BinaryTree<elemType> :: InOrder(Node<elemType> *t) const {
    if (!t) return; // also deal with the root case  
    InOrder(t->left_);
    std::cout << t->data_ << " ";
    InOrder(t->right_);
}
template <class elemType>
void BinaryTree<elemType> :: PostOrder(Node<elemType> *t) const {
    if (!t) return; // also deal with the root case
    PostOrder(t->left_);
    PostOrder(t->right_);
    std::cout << t->data_ << " ";
}

/* 
  Non-Recursive algorithm implementation,
*/

template <class elemType>
void BinaryTree<elemType>::PreOrder_nr(void) const {
  if (!root_) return;
  Node<elemType> *p;
  SeqStack<Node<elemType> *> s1;
  s1.push(root_);

  while (!s1.isEmpty()) {
    p = s1.pop();
    std::cout << p->data << " ";
    if (p->right_) s1.push(p->right_);
    if (p->left_)  s1.push(p->left);
  }
  std::cout << std::endl;
}

/* 
  Time Complexity: O(2n)
  Characteristic of Stack: above element go first:
  So when visiting the root first, hold it still and:
    Pull the left subtree to the stack
  Then we hold it to the InOrder traversal.
  Similar for the PosrOrder_nr
*/ 

template <class elemType>
void BinaryTree<elemType>::InOrder_nr(void) const {
  if (!root_) return;

  SeqStack<Node<elemType> *> s1;
  SeqStack<int> s2;
  Node<elemType> *p;
  int flag;
  p = root_;
  s1.push(root_);
  s2.push(0);
  
  while (!s1.isEmpty()) {
    flag = s2.pop();
    p = s1.top();
    if (flag == 1) {
      s1.pop();
      std::cout << p->data_ << " ";
      if (p->right_) {
        s1.push(p->right_);
        s2.push(0);
      }
    } else {
      s2.push(1);
      if (p->left_) {
        s1.push(p->left_);
        s2.push(0);
      }
    }//if
  }//while
  std::cout << std::endl;
}

template <class elemType>
void BinaryTree<elemType>::PostOrder_nr(void) const {
  if (!root_) return;

  SeqStack<Node<elemType> *> s1;
  SeqStack<int> s2;
  Node<elemType> *p;
  int flag;
  
  p = root_;
  s1.push(root_);
  s2.push(0);
  while (!s1.isEmpty()) {
    flag = s2.pop();
    p = s1.top();
    switch (flag)
    {
    case 2:
      s1.pop();
      std::cout << p->data_ << " ";
      break;
    case 1:
      s2.push(2);
      if (p->right_) {
        s1.push(p->right_);
        s2.push(0);
      }
      break;
    default:  // case 0
      s2.push(1);
      if (p->left_) {
        s1.push(p->left_);
        s2.push(0);
      }
      break;
    }//switch
  }//while
  std::cout << std::endl;
}

/*
    No flag stack implementation, O(n)
    The trick is: since we firstly visit every left child first,
    We may push them at a time !
    Less (1n) complexity
*/
template <class elemType>
void BinaryTree<elemType>::InOrder_nr2(void) const {
  if (!root_) return;
  SeqStack<Node<elemType> *> s;
  Node<elemType> *p;
  p = root_;
  while (p) {
    s.push(p);
    p = p->left_;
  }

  while (!s.isEmpty()) {
    p = s.pop();
    std::cout << p->data_ << " ";
    if (p->right_) {
      p = p->right_;
      while (p) {
        s.push(p);
        p = p->left;
      }
    }
  }
  std::cout << std::endl;
}


/* The similar idea to the InOrder_nr2 */

template <class elemType>
void BinaryTree<elemType>::PostOrder_nr2(void) const {
  if (!root_) return;

  SeqStack<Node <elemType> *> s1;
  SeqStack<int> s2;
  Node<elemType> *p;
  int flag;
  p = root_;

  while (p) {
    s1.push(p);
    s2.push(0);
    p = p->left_;
  }
  while (!s1.isEmpty()) {
    p = s1.top();
    flag = s2.pop();
    if (flag == 1) {
      s1.pop();
      std::cout << p->data_ << " ";
    } else {  // flag == 0
      s2.push(1);
      if (p->right_) {
        p = p->right_;
        while (p) {
          s1.push(p);
          s2.push(0);
          p = p->left_;
        }
      }
    }//if
  }//while
  std::cout << std::endl;
}


// BFS, using Queue, similar to the creating process
template <class elemType>
void BinaryTree<elemType>::LevelOrder(void) const {
  if (!root_) return;

  SeqQueue<Node<elemType> *> q;
  Node<elemType> *p;
  q.enQueue(root_);
  while (!q.isEmpty()) {
    p = q.deQueue();
    std::cout << p->data_ << " ";
    
    if(p->left_) q.enQueue(p->left_);
    if(p->right_) q.enQueue(p->right_);
  }
  std::cout << std::endl;
}


/*
  Use queue to judge whether the binary tree is COMPLETE BinaryTree or not
*/
template <class elemType>
bool BinaryTree<elemType>::isComplete(void) const {
  SeqQueue<Node<elemType> *> q;
  Node<elemType> *p;
  if (root_) q.enQueue(root_);
  p = q.getFront();
  // Level-traversal, add each node(including NULL in queue) and pop the parent
  while (p) {
    q.enQueue(p->left_);
    q.enQueue(p->right_);
    p = q.deQueue();
  }
  // if existing non-NULL node in the queue, false
  while (!q.isEmpty()) {
    if (q.getFront()) return false;
    q.deQueue();
  }
  return true;
}


/*
    Build a tree from its PreOrder and Inorder
    Recursive implementation
*/
template <class elemType>
Node<elemType> *BinaryTree<elemType>:: 
BuildFromPreIn(elemType pre[], int pl, int pr,
               elemType in[], int il, int ir) {
  if (pl > pr) return NULL;
  Node<elemType> *p;
  Node<elemType> *leftRoot;
  Node<elemType> *rightRoot;
  int i;
  int pos;
  int num;
  // left-subtree: pre[lpl,lpr], in[lil,lir]
  int lpl;
  int lpr;
  int lil;
  int lir; 
  // right-subtree: pre[rpl,rpr], in[ril,rir]
  int rpl;
  int rpr;
  int ril;
  int rir; 
  p = new Node<elemType>(pre[pl]); // new node according to the found root, in PreOrder
  if (!root_) root_ = p;
  // find root in the InOrder, index=i
  for (i = il; i < ir; i++)
    if (in[i] == pre[pl]) break;
  pos = i; // index of root in the InOrder
  num = pos - il; // size of subtree
  // find index range of left subtree, return the built subtree(down-top)
  // note that pl is root 
  lpl = pl + 1;
  lpr = pl + num;
  lil = il;
  lir = pos - 1;
  leftRoot = BuildFromPreIn(pre,lpl,lpr,in,lil,lir);
  // find index range of right subtree, return the built subtree(down-top)
  rpl = pl + num +1; 
  rpr = pr;
  ril = pos + 1; 
  rir = ir;
  rightRoot = BuildFromPreIn(pre,rpl,rpr,in,ril,rir);
  
  p->left_     = leftRoot;
  p->right_    = rightRoot;
  return p;
}

template <class elemType>
Node<elemType> *BinaryTree<elemType>::
BuildFromInPost(elemType in[], int il, int ir, 
                elemType post[], int pl, int pr) {
  if (pl > pr) return NULL;
  Node<elemType> *p;
  Node<elemType> *leftRoot;
  Node<elemType> *rightRoot;
  int i;
  int pos;
  int num;
  // left-subtree: post[lpl,lpr], in[lil,lir]
  int lpl;
  int lpr;
  int lil;
  int lir; 
  // right-subtree: post[rpl,rpr], in[ril,rir]
  int rpl;
  int rpr;
  int ril;
  int rir; 
  p = new Node<elemType>(post[pr]); // new node according to the found root, in PostOrder
  if (!root_) root_ = p;
  // find root in the InOrder, index=i
  for (i = il; i < ir; i++)
    if (in[i] == post[pr]) break;
  pos = i; // index of root in the InOrder
  num = pos - il; // size of subtree
  // find index range of left subtree, return the built subtree(down-top)
  // note that pl is root 
  lpl = pl; 
  lpr = pl + num -1;

  lil = il; 
  lir = pos - 1;
  leftRoot = BuildFromInPost(in,lil,lir, post,lpl,lpr);
  // find index range of right subtree, return the built subtree(down-top)
  rpl = pl + num; 
  rpr = pr - 1;
  ril = pos + 1; 
  rir = ir;
  rightRoot = BuildFromInPost(in,ril,rir,post,rpl,rpr);
  p->left_     = leftRoot;
  p->right_    = rightRoot;
  return p;
}
