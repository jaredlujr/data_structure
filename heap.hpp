#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#include <vector>

#define LEFT(idx)     ( (idx << 1) + 1)
#define RIGHT(idx)    ( (idx << 1) + 2)
#define PARENT(idx)   ( (idx-1) >>  1  )

// leftchild    = (i<<1)+1; 
// rightchild   = (i<<1)+2; 
// parent       = (i-1)>>1;


//swap
template <class T>
void swap_foo(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
    // a = a + b; b = a - b; a =  a - b; //using "+", it may be out of range 
    // a = a ^ b; b = b ^ a; a = a ^ b; // using xor
}



/* 
    Heap class: 
        - The minimal element is on the root;
        - Any subtree is also MinHeap
        - Indexing heap as follows:
            Table1: Natural index [0,1,2,..,n-1], n elements <int>, * mark the position of heap * 
            Table2: Data table [d0,d1,...,dn-1], n elements <T>,  * store the data for comparison * 
            Table3: Index table [i0,i1,...,in-1], n elements <int>, * pos -> rank*
            Table4: Reverse table [r0,r1,..,rn-1], n elements <int>, * rank -> pos *
*/
template <class elemType>
class MinHeap
{
    private:

        int currentSize;
        vector<T> array;  
        vector<int> index;
        vector<int> query;
    
    public:
        // constructor
        MinHeap(void): currentSize(0), array(10), index(10), query(10){};
        MinHeap(vector<T> nums): currentSize(nums.size()),array(nums.size()),index(nums.size()),query(nums.size())
        {
            // construct from seqlist
            // O(N)
            int i;
            for(i=0;i<nums.size();i++)
            {
                array[i] = nums[i];
                query[i] = i;
                index[i] =i;
            }
            buildHeap();
        }

        int size(void) const {return currentSize;}
        int isEmpty(void) const {return currentSize==0;}
        void getTop(void) const {cout << index[0] + 1 << " " << array[0] << endl;}

        void buildHeap(void)
        {
            int i;
            // the largest non-leaf node
            for(i=PARENT(currentSize-1);i>=0;i--)
                heapify(i);
        }

        /*
            To push, we craete a hole at next empty node
            And one by one compare with its parent
            Till it reaches the right position
            Return the position in heap_array for convenience
            
            :: Bottom-Up, hole == 0 -> root
        */
        void push(const T &x)
        {
            // double space
            if(currentSize == array.size())
            {
                array.resize(array.size() * 2);
                index.resize(array.size() * 2);
                query.resize(query.size() * 2);
            }
            
            // hole = the position for new element
            int hole = currentSize;
            
            while( hole > 0  && x < array[PARENT(hole)] )
            {
                // parent shift down
                array[hole] = array[PARENT(hole)];
                index[hole] = index[PARENT(hole)];
                query[index[hole]] = hole; 

                // next
                hole = PARENT(hole);
            }
            // data fill in
            array[hole] = x;
            index[hole] = currentSize;
            // The last in, no account for delete
            query[currentSize] = hole;

            currentSize++;
            
        }
       
        void heapify(int i)
        {
            // All are leaf nodes
            if( i >= currentSize / 2 )    return;
            
            // initialize the smallest as present root
            int smallest = i; 
            int l = LEFT(i);
            int r = RIGHT(i);
            
            // if left child is larger
            if (l < currentSize )
                if( (array[l] < array[smallest]) || (array[l]==array[smallest] && index[l] < index[smallest] ))
                    smallest = l;
            
            // if right child is larger
            if (r < currentSize )
                if( (array[r] < array[smallest]) || (array[r]==array[smallest] && index[r] < index[smallest] ))
                    smallest = r;
            
            // if smallest is not present root, do swapping
            if (smallest != i)
            {
                swap_foo(array[smallest], array[i]);
                swap_foo(index[smallest], index[i]);
                swap_foo(query[index[smallest]],query[index[i]]);
                // recursively heapify the 'affected' sub-tree (l- r- child as root), 
                // because we changed the heapified subtree!
                heapify(smallest);
            }
        }
        
        // adjust the element @[id], id is the coming rank
        void add(int id, int delta)
        {   
            // return the id in heap-array
            int i;
            i =  query[id];
            array[i] += delta;
            // node i, i is index in heap
            while(1)
            {
                heapify(i);
                if(i==0)
                    break;
                i = PARENT(i);
            }
        }

        T deleteMin(void)
        {
            T min_element = array[0];
            // put the last element at root
            array[0] = array[currentSize-1];
            currentSize--;
            // percolate down to maintain the heap
            heapify(0);
            return min_element;
        }    

};