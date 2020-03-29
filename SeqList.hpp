#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif


#ifndef LIST
    #define LIST
    #include "List.hpp"
#endif


/* This is source code for implementation of sequential list, 
    utilize the templated class with some member functions */


// sequential list declaration
template <class elemType>
class SeqList: public List <elemType>
{
    private:
        elemType *data;
        int currentLength;
        int maxSize;
        void doubleSpace(void); // extend the present list, Dynamically
    public:
        SeqList(int initSize=30); //construction
        ~SeqList(){delete [] data;} //deconstruction, data is allocated from heap
        int length(void) const;
        int index(const elemType &x)  const;
        elemType visit(int i)  const;
        void insert(int i, const elemType &x);
        void remove(int i);
        void clear(void);
        void traverse(void) const;
};


/* Specific member functions of SeqList*/

template <class elemType>
SeqList <elemType>:: SeqList(int initSize) // initSize has been DEFINED as 30, here is the interface
{
    //impilit writing "this" pointer
    data = new elemType[initSize];
    if (!data)  // check it
        throw IllegalSize(); 
    maxSize = initSize;
    currentLength = 0; // setting zero
}

template <class elemType>
int SeqList <elemType>:: length(void) const
{
    return currentLength;
}

template <class elemType>
int SeqList <elemType>:: index(const elemType &x) const
{
    int i = 0;
    for(i=0;i<currentLength;i++)
    {
        if(data[i]==x)
        {
            break;
        }
    }
    if(i==currentLength) // check it
        return -1;
    else
        return i;
}

template <class elemType>
elemType SeqList <elemType>:: visit(int i) const
{
    if(i>=0 && i<currentLength) 
        return data[i];
    else
        throw OutOfBound(); // check it
}

// private member: in order to extend the list due to the meet of boundary
template <class elemType>
void SeqList <elemType>:: doubleSpace(void)
{
    int j=0;
    elemType *tmp = new elemType[maxSize * 2];
    if(!tmp) throw IllegalSize(); // check it
    for(j=0;j<currentLength;j++)
    {
        tmp[j] = data[j];
    }
    delete [] data;
    data = tmp;
    maxSize *= 2;
}


template <class elemType>
void SeqList <elemType>:: insert(int i, const elemType &x)
{
    int j=0;
    if(i> currentLength || i< 0)// check it
    {
        throw OutOfBound();
        return;
    }
    if(currentLength==maxSize)
        doubleSpace();
    
    for(j=currentLength;j>i;j--) //"accept" the last one, till data[i] -> data[i+1]
        data[j] = data[j-1];
    
    data[i] = x;
    currentLength++; // update after each revision
}


template <class elemType>
void SeqList <elemType>:: remove(int i)
{
    int j = 0;
    if(i>= currentLength || i < 0)// check it
    {
        throw OutOfBound();
        return;
    }
    for(j=i;j<currentLength-1;j++)
        data[j] = data[j+1];
    currentLength--;
}

template <class elemType>
void SeqList <elemType>:: clear(void)
{
    currentLength = 0;
}

template <class elemType>
void SeqList <elemType>:: traverse(void) const
{
    int j = 0;
    cout << "[";
    for (j=0;j<currentLength;j++)
        cout << this->visit(j) << " ";
    cout << "]" << endl;
}

