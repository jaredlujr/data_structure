/* 
    Find the smallest consuming E:
    Merge n-ary apples in heaps, one can only merge a pair at a time, and this consume E+=(h1+h2) energy
    Using the algorithm of building Huffmann Tree: 
        to merge the 2-smallest ones in the array
    
    Implementation: binary heap / priority_queue

*/
#ifndef IOSTD
#define IOSTD
#include <iostream>
using namespace std;
#endif

#include "heap.hpp"


int main(void)
{
    int n,i,q;
    cin >> n;

    
    /*
    // Week8-hw1

    long energy=0;
    while(h.size() > 1)
    {
        long tmp1 = h.deleteMin();
        long tmp2 = h.deleteMin();
        long result = tmp1+tmp2;
        energy += result;
        h.insert(result);
    }
    cout << energy << endl;
    */

    // Week8-hw2
    MinHeap<int> h;
    

    for(i=0;i<n;i++){
        int x;
        cin >> x;
        h.push(x);
    }
        
    cin >> q; // operations
    string op;
    for(i=0;i<q;i++)
    {
        cin >> op;
        if(op=="add")
        {
            int id,delta;
            cin >> id >> delta;
            // query index mapping to heap index
            h.add(id-1,delta);
        }
        else// query
        {
            h.getTop();
        }
        
    }
    return 0;

}
