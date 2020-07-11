#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef ERRORS
    #define ERRORS
    #include "errors.hpp"
#endif

/* 
    leftchild    = (i<<1); 
    rightchild   = (i<<1)+1; 
    parent       = i>>1;
*/
#define LEFT(i)     ( (i << 1) )
#define RIGHT(i)    ( (i << 1) + 1)
#define PARENT(i)   ( i >>  1  )



/* 
    Priority Queue/ MinHeap class: 
        - The minimal element is on the root(array[1]);
        - The last leaf node is array[currentSize]
        - The last non-leaf node is array[PARENT(currentSize)]
        - Any subtree is also MinHeap
        - The partial order can be re-defined
*/
template <class elemType>
class PriorityQueue
{
    private:
        elemType *array;
        int maxSize;
        int currentSize;
        
        virtual void doubleSpace(void);
        virtual void buildHeap(void);
        virtual void percolateDown(int hole);
    public:
        // Build from empty, only feed the Max Size
        PriorityQueue(int capacity=100) 
        {
            array = new elemType[capacity];
            // Check memory allocation
            if(!array) throw IllegalSize();
            maxSize = capacity;
            currentSize = 0;
        }
        // Build from Sequential List
        PriorityQueue(const elemType *data,int size);
        ~PriorityQueue(){delete [] array;}
        virtual bool isEmpty(void) const {return currentSize==0;}
        // Index(root) from 1, 0 storing nothing
        virtual elemType getHead(void) const {return array[1];}
        virtual void enQueue(const elemType &x);
        elemType deQueue(void);
};



template <class elemType>
void PriorityQueue <elemType>:: doubleSpace(void)
{
    int j=0;
    elemType *tmp = new elemType[maxSize * 2];
    if(!tmp) throw IllegalSize(); 
    // Assign the primal value
    for(j=0;j<currentSize;j++)
        tmp[j+1] = array[j+1];
    delete [] array;
    array = tmp;
    maxSize *= 2;
}

template <class elemType>
void PriorityQueue<elemType>:: percolateDown(int hole)
{
    int child;
    // Store the hole element temporarily
    elemType tmp = array[hole];
    
    
    for(; LEFT(hole)<=currentSize; hole = child )
    {
        // Between two children, find the smallest one, say along this path
        child = LEFT(hole); 
        if(LEFT(hole) != currentSize && array[RIGHT(hole)] < array[LEFT(hole)])
            child = RIGHT(hole);
        // Move up the descendant along the path if ok
        if(array[child] < tmp )
            array[hole] = array[child];
        else 
            break;
    }
    // Posit the element
    array[hole] = tmp;
}


template <class elemType>
void PriorityQueue<elemType>:: enQueue(const elemType &x)
{
    // isFull
    if(currentSize==maxSize - 1)    doubleSpace();

    /* Below codes to do percolating Up */
    // Add another position, and list length++
    int hole = ++currentSize;
    for(; hole > 1 && x < array[PARENT(hole)]; hole=PARENT(hole))
        array[hole] = array[PARENT(hole)];
    // Terminal case: x==1 or x > array[PARENT(hole)]
    array[hole] = x;
}

template <class elemType>
elemType PriorityQueue<elemType>:: deQueue(void)
{
    elemType minimum = array[1];
    // Shrink the List and put the last one in proper pos
    array[1] = array[currentSize--];
    percolateDown(1);
    return minimum;
}


template <class elemType>
void PriorityQueue<elemType>:: buildHeap(void)
{
    int i;
    /* 
        Percolate Down all the non-leaf node
        The leaf node can be viewed as In-Place
    */
    for(i=PARENT(currentSize);i>0;i--)
        percolateDown(i);
}

template <class elemType>
PriorityQueue<elemType>:: PriorityQueue(const elemType *data, int size)
: maxSize(size+10), currentSize(size)
{
    int i;
    array = new elemType[maxSize];
    if(!array) throw IllegalSize();
    for(i=0;i<size;i++)
        array[i+1] = data[i];
    buildHeap();
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
class IndexHeap: public PriorityQueue<elemType>
{
    private:
        // Reverse Indexing Heap, also record the original index of elements
        elemType *array;
        int *index;
        int *query;
        int maxSize;
        int currentSize;
        
        void doubleSpace(void);
        void buildHeap(void);
        void percolateDown(int hole);

    public:
        IndexHeap(int capacity=100)
        {
            array = new elemType[capacity];
            index = new int[capacity];
            query = new int[capacity];
            
            // Check memory allocation
            if(!array) throw IllegalSize();
            if(!index) throw IllegalSize();
            if(!query) throw IllegalSize();

            maxSize = capacity;
            currentSize = 0;
        }
        IndexHeap(const elemType *data,int size);
        ~IndexHeap(){delete [] array; delete [] index; delete [] query;}
        bool isEmpty(void) const {return currentSize==0;}
        elemType getHead(void) const {return array[1];}
        int minIndex(void) const {return index[1];}// Return the index of the top element
        void enQueue(const elemType &x);
};


template <class elemType>
void IndexHeap <elemType>:: doubleSpace(void)
{
    int j=0;

    elemType *tmp  = new elemType[maxSize * 2];
    int *tmp_index = new int[maxSize * 2];
    int *tmp_query = new int[maxSize * 2];

    // Check memory allocation
    if(!tmp)        throw IllegalSize();
    if(!tmp_index)  throw IllegalSize();
    if(!tmp_query)  throw IllegalSize();

    // Assign the primal value
    for(j=1;j<=currentSize;j++)
    {
        tmp[j] = array[j];  // root == array[1]
        tmp_index[j] = index[j];   // index from 0
        tmp_query[j] = query[j];   // index from 
    }

    delete [] array;
    delete [] index;
    delete [] query;
    array = tmp;
    index = tmp_index;
    query = tmp_query;

    maxSize *= 2;
}


template <class elemType>
void IndexHeap<elemType>:: percolateDown(int hole)
{
    int child;
    // Store the hole element temporarily
    elemType tmp    = array[hole];
    int pos         = hole;
    int pindex      = index[hole];
    
    
    for(; LEFT(hole)<=currentSize; hole = child )
    {
        // Between two children, find the smallest one, say along this path
        child = LEFT(hole); 
        if(LEFT(hole) != currentSize && array[RIGHT(hole)] < array[LEFT(hole)])
            child = RIGHT(hole);
        // Move up the descendant along the path if ok
        if(array[child] < tmp )
        {
            array[hole] = array[child];
            index[hole] = index[child];
            query[index[hole]] = hole;
        }
        else 
            break;
    }
    // Posit the element
    array[hole]     = tmp;
    index[hole]     = pindex;
    query[pindex]   = pos;
}


template <class elemType>
void IndexHeap<elemType>:: enQueue(const elemType &x)
{
    // isFull
    if(currentSize==maxSize - 1)  doubleSpace();

    /* Below codes to do percolating Up */
    // Add another position, and list length++
    int hole = ++currentSize;

    for(; hole > 1 && x < array[PARENT(hole)]; hole=PARENT(hole))
    {
        array[hole] = array[PARENT(hole)];
        index[hole] = index[PARENT(hole)];
        query[index[hole]] = hole;
        
    }
    // Terminal case: x==1 or x > array[PARENT(hole)]
    array[hole] = x;
    index[hole] = currentSize;
    query[currentSize] = hole;
}


template <class elemType>
void IndexHeap<elemType>:: buildHeap(void)
{  
    /* 
        Percolate Down all the non-leaf node
        The leaf node can be viewed as In-Place
    */
    int i;
    for(i=PARENT(currentSize);i>0;i--)
        percolateDown(i);
}


template <class elemType>
IndexHeap<elemType>:: IndexHeap(const elemType *data, int size)
: maxSize(size+10), currentSize(size)
{
    int i;
    array = new elemType[maxSize];
    if(!array) throw IllegalSize();
    for(i=1;i<=size;i++)
    {
        array[i] = data[i-1];
        index[i] = i;
        query[i] = i;
    }
    buildHeap();
}