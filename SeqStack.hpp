#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef Stack
    #define Stack
    #include "Stack.hpp"
#endif


/* IMPLEMENTATION of Sequential stack */

template <class elemType>
class SeqStack: public Stack<elemType>
{
    private:
        elemType *elem;
        int ptop;
        int maxSize;
        
        void doubleSpace(void);
    public:
        SeqStack(int initSize=10);
        ~SeqStack();

        bool isEmpty(void) const;
        elemType top(void) const;
        elemType pop(void) const;
        void push(const elemType &x);
};

template <class elemType>
SeqStack<elemType>:: SeqStack(int initSize=10)
{
    maxSize = initSize;
    ptop = 0;
}
