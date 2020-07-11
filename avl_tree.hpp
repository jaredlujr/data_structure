#ifndef
#define DYNAMIC_SEARCH_TABLE_H_
#include "dynamic_search_table.hpp"
#endif

template <class KEY, class OTHER>
class AvlTree : public DynamicSearchTable<KEY, OTHER> {
 public:
  AvlTree(void){root_ = NULL;}
  ~AvlTree(){MakeEmpty(root_);}
  SET<KEY, OTHER> *Find(const KEY &x) const; // Same as BinarySearchTree, non-recursive
  void Insert(const SET<KEY, OTHER> &x){Insert(x, root_);}
  void Remove(const KEY &x){Remove(x, root_);}
 private:
  struct AvlNode {
    SET<KEY, OTHER> data_;
    AvlNode *left_, *right_;
    int height_;  // Height of current AvlNode
    AvlNode(const SET<KEY, OTHER> &element, AvlNode *lt=NULL, AvlNode *rt=NULL, int h=1)
      : data_(element), left_(lt), right_(rt), height_(h){}
  };
  AvlNode *root_;
  void Insert(const SET<KEY, OTHER> &x, AvlNode * &t);
  bool Remove(const KEY &x, AvlNode * &t);
  void MakeEmpty(AvlNode * &t);
  int height(AvlNode * &t) const {return (t == NULL) ? 0 : t->height;}
  // Rotate BinaryTree
  void LL(AvlNode * &t);
  void RR(AvlNode * &t);
  void LR(AvlNode * &t);
  void RL(AvlNode * &t);
  int Max(int a, int b){return (a > b) ? a : b;}
  bool Adjust(AvlNode * &t, int subTree);
};


template <class KEY, class OTHER>
SET<KEY,OTHER> * AvlTree<KEY,OTHER>::Find(const KEY &x) const {
  AvlNode *p = root_;
  while(p != NULL && p->data_.KEY != x)
  {
    if (x < p->data_.key) 
      p = p->left_; // Shift 
    else 
      p = p->right_;  // Shift
}
  if (!p)
    return NULL;
  else
    return (SET<KEY, OTHER> *) p;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::Insert(const SET<KEY, OTHER> &x, AvlNode * &t) {
  if (!t) {  // Empty tree
    t = new AvlNode(x);
  } else if (x.key < t->data_.key) {  // Left subtree
    Insert(x, t->left_);
    if (height(t->left_) - height(t->right_) == 2) {  // Lose balance
      if (x.key < x->left_->data_.key)  // The insert is LL pattern
        LL(t);
      else
        LR(t);
    }
    } else if (x.key > t->data_.key) {  // Left subtree
    Insert(x, t->right_);
    if (height(t->left_) - height(t->right_) == -2) {  // Lose balance
      if (x.key < x->left_->data_.key)  // The insert is LL pattern
        RL(t);
      else
        RR(t);
    }
    }
  // Node t may be influenced
  t->height = max(height(t->left_), height(t->right_)) + 1;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode * &t) {  
  AvlNode *tmp = t->left_;  // Future root (position of t)
  t->left_ = tmp->right_;  // Detach
  tmp->right_ = t;
  // Adjust the height of affected node
  t->height = max(height(t->left_), height(t->right_)) + 1;
  tmp->height = max(height(tmp->left_), height(t)) + 1;
  // Assign
  t = tmp;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode * &t) {  
  AvlNode *tmp = t->right_;  // Future root (position of t)
  t->right_ = tmp->left_;  // Detach
  tmp->left_ = t;
  // Adjust the height of affected node
  t->height = max(height(t->left_), height(t->right_)) + 1;
  tmp->height = max(height(tmp->right_), height(t)) + 1;
  // Assign
  t = tmp;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode * &t) {
  RR(t->left_);
  LL(t);
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode * &t) {
  LL(t->right_);
  RR(t);
}

/* To give a flag about whether delete has been done, recursively */
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::Remove(const KEY &x, AvlNode * &t){
  if (!t) return true;
  if ( x == t->data_.key) {  // Delete the root of t
    if (t->left_ == NULL || t->right_ == NULL) {  // Leaf node
      AvlNode *oldNode = t;
      t = (t->left_ != NULL) ? t->left_ : t->right_;
      delete oldNode;
      return false;
    } else {  // Find substitude from right subtree
      AvlNode *tmp = t->right_;
      while (tmp->left_ != NULL) 
        tmp = tmp->left_;
      t->data_ = tmp->data_;
      if (Remove(tmp->data_.key, t->right_)) return true;  // true == delete done
      return Adjust(t, 1);
    }
  } else if (x < t->data_.key) {
    if (Remove(x, t->left_)) return true;
    return Adjust(t, 0);
  } else {
    if (Remove(x, t->right_)) return true;
    return Adjust(t, 1);
  }
}

/* To give a flag indicating whether some subtree is shortened */
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::Adjust(AvlNode * &t, int subTree) {
  if (subTree == 1) {  // Delete at right subtree, may render it shortened
    if (height(t->left_)- height(t->right_) == 1) return true;
    if (height(t->right_) == height(t->left_)) {--t->height; return false;}
    if (height(t->left_->right_ > height(t->left_->left_))) {LR(t); return false;}
    LL(t);
    if (height(t->right_) == height(t->left_)) 
      return false;
    else
      return true;
  }
  else {  // Delete at left subtree
    if (height(t->left_)- height(t->right_) == -1) return true;
    if (height(t->right_) == height(t->left_)) {--t->height; return false;}
    if (height(t->right_->left_ > height(t->right_->right_))) {RL(t); return false;}
    RR(t);
    if (height(t->right_) == height(t->left_)) 
      return false;
    else
      return true;
  }
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::MakeEmpty(AvlNode * &t) {
  if(!t) return;

  AvlNode *leftTree = t->left_;
  AvlNode *rightTree = t->right_;
  delete t;
  MakeEmpty(leftTree);
  MakeEmpty(rightTree);
}