#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif


/*
    Static method: binary search
    Binary Search for any comparable sorted array.
*/
template <class elemType>
int BinarySearch(elemType arr[], int length, const elemType &x) {
  int low=0;
  int high = length;
  int mid;
  while (low<=high) {
    mid = low + (high-low)/2;
    if (arr[mid] == x) {
      return mid;
    } else if (arr[mid] > x) {    // between arr[low] and arr[mid]
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return low;
}

// For initialization use, generating the sequence till fib[k-1]
void getFibSeq(int *fib, int k) {
  fib[0] = 1;
  fib[1] = 1;
  for (int i = 2; i < k; i++) {
      fib[i] = fib[i - 1] + fib[i - 2];
  }
}



template <class KEY,class OTHER>
class SET {
 public:
  KEY key;
  OTHER other;
};

/*
    Dynamic methods, abstract class
*/

template <class KEY,class OTHER>
class DynamicSearchTable
{
    public:
        virtual SET<KEY,OTHER> *find(const KEY &x) const = 0;
        virtual void insert(const SET<KEY,OTHER> &x) = 0;
        virtual void remove(const KEY &x) = 0;
        virtual ~DynamicSearchTable(){};
};


/*
    Binary search tree
*/

template <class KEY,class OTHER>
class BinarySearchTree: public DynamicSearchTable<KEY,OTHER>
{
    private:
        // embedded struct for each record
        struct BinaryNode
        {
            SET<KEY,OTHER> data;
            BinaryNode *left;
            BinaryNode *right;
            // constructor
            BinaryNode(const SET<KEY,OTHER> &thedata,
                    BinaryNode *lt=NULL,BinaryNode *rt=NULL): data(thedata), left(lt), right(rt){}
        };
        // Entrance
        BinaryNode *root;
        // Use t as lvalue inside the function
        void insert(const SET<KEY,OTHER> &x, BinaryNode * &t);
        void remove(const KEY &x, BinaryNode * &t);
        SET<KEY,OTHER> *find(const KEY &x, BinaryNode *t) const;
        void makeEmpty(BinaryNode *t);
    public:
        BinarySearchTree(void){ root=NULL;  }
        ~BinarySearchTree(){};
        void insert(const SET<KEY,OTHER> &x);
        void remove(const KEY &x);
        SET<KEY,OTHER> *find(const KEY &x) const;
};


/* 
    Recursive implementation example
    Adapt with `return find(x,root)` for public find()
*/
template <class KEY,class OTHER>
SET<KEY,OTHER> * BinarySearchTree<KEY,OTHER>:: find(const KEY &x, BinaryNode * t) const 
{
    if(t==NULL) return NULL;
    else if(t->data.key == x) return (SET<KEY,OTHER> *)t;
    /* 
        //Write in one sentence:
        if(t==NULL || t->data.key==x) return (SET<KEY,OTHER> *)t;
    */
   if(x < t->data.key) return find(x,t->left);
   else return find(x,t->right);
}
/*
    Non-recursive implementation
*/
template <class KEY,class OTHER>
SET<KEY,OTHER> * BinarySearchTree<KEY,OTHER>:: find(const KEY &x) const
{
    if(!root) return NULL;
    BinaryNode *p = root;
    while(p)
    {
        if(x==p->data.key) return &(p->data);
        else if(x<p->data.key) p = p->left; // Shift 
        else p = p->right;  // Shift
    }
    // No finding
    return NULL;
}

/*
    Non-recursive implementation.
    Any new node is leaf.
    Complexity: O(height) --balanced tree--> O(logN)
*/
template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER> :: insert(const SET<KEY,OTHER> &x)
{
    if(!root) 
    {
        root = new BinaryNode(x);
        return;
    }
    BinaryNode *p = root;
    while(p)
    {
        if(x.key == p->data.key) return;
        else if(x.key < p->data.key)
        {
            // Left child is empty, end loop and insert
            if(!p->left)
            {
                p->left = new BinaryNode(x);
                return;
            }
            p = p->left;
        }
        else
        {
            if(!p->right)
            {
                p->right = new BinaryNode(x);
                return;
            }
            p = p->right;
        }//if
    }//while
}

/*
    Remove: non-recursive implementation
    There are three cases:
        1. Remove leaf
        2. Remove Single-Child node
        3. Remove Double-CHild node
*/

template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>:: remove(const KEY &x)
{
    if(!root) return;
    // Double pointer traversal
    BinaryNode *p,*parent;
    // 0 for left path, 1 for right path
    int flag;
    p = root;
    parent = NULL;
    
    // 
    while(p)
    {
        if(x<p->data.key) // Shift Left
        {
            parent = p;
            flag = 0;
            p = p->left;
            continue;
        }
        else if(x>p->data.key) // Shift Right
        {
            parent = p;
            flag = 1;
            p = p->right;
            continue;
        }

        // Remove as follows
        if(!p->left && !p->right) // Leaf case
        {
            delete p;
            if(!parent) {root = NULL; return;}// root as leaf such that parent==NULL
            if(flag==0) // Removed node is left child
                parent->left = NULL;
            else        // Removed node is right child
                parent->right = NULL;
        }
        else if(!p->left || !p->right) // Single-Child case
        {
            BinaryNode *tmp = p;
            if(!parent) // root
            root = (p->left)?(p->left):(p->right);
            else
            {
                // Connect parent and child
                if(flag==0) // Connect parent and child
                    parent->left = (p->left)?(p->left):(p->right);
                else
                    parent->right = (p->left)?(p->left):(p->right);
            }
            delete tmp;
            return;
        }
        else // Double-Child case
        {
            // Utilize extra pointer to find the "left neighbor" in InOrder
            // which is the substitude of removed node
            BinaryNode *substitute;
            parent = p;
            substitute = p->left; // Along its left subtree
            flag = 0;
            while(substitute->right)
            {
                parent = substitute;
                flag = 1;
                substitute = substitute->right;
            }
            // Now substitute has no right child, but substitute is not NULL
            // Let substitute cover p , then delete substitute
            SET<KEY,OTHER> e;
            e = p->data;
            p->data = substitute->data;
            substitute->data = e;
            // Swap these two pointers and back to loop(delete as leaf case)
            p = substitute;
        }
    }//while
}




