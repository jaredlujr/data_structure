#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef STACK
    #define STACK
    #include "Stack.hpp"
#endif


/* IMPLEMENTATION of Sequential stack */

template <class elemType>
class SeqStack: public Stack <elemType>
{
    private:
        elemType *elem;
        int Top;
        int maxSize;
        
        void doubleSpace(void);
    public:
        SeqStack(int initSize=10);
        ~SeqStack();

        bool isEmpty(void) const;
        elemType top(void) const;
        elemType pop(void);
        void push(const elemType &x);
};

/* initialization of sequential stack -> empty*/
template <class elemType>
SeqStack<elemType>:: SeqStack(int initSize)
{
    elem = new elemType[initSize];
    if(!elem) throw IllegalSize();
    maxSize = initSize;
    Top = -1;
}

template <class elemType>
SeqStack<elemType>:: ~SeqStack()
{delete [] elem;} // free the non-auto data


template <class elemType>
bool SeqStack<elemType>:: isEmpty(void) const
{return (Top==-1);}


template <class elemType>
elemType SeqStack<elemType>:: top(void) const
{
    if(Top==-1) // argument check
        throw OutOfBound(); 
    return elem[Top];
}

template <class elemType>
elemType SeqStack<elemType>:: pop(void)
{
    if(Top == -1)
        throw OutOfBound();

    return elem[Top--];
}

// worst: O(n) complexity due to doubleSpace; O(1) average;
template <class elemType>
void SeqStack<elemType>:: push(const elemType &x)
{
    if(Top == maxSize -1 )
        doubleSpace();
    elem[++Top] = x;
}

template <class elemType>
void SeqStack<elemType>:: doubleSpace(void)
{
    int i;
    elemType *tmp = elem;
    elem = new elemType[2*maxSize];
    for(i = 0;i<maxSize;i++)
        elem[i] = tmp[i];
    maxSize *= 2;
    delete []tmp;
}

