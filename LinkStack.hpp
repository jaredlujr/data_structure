#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef STACK
    #define STACK
    #include "Stack.hpp"
#endif


/* linked stack implementation, for linked stack, complexity = O(1), because all operatirons afre for top */
template <class elemType>
class LinkStack: public Stack <elemType>
{
    private:
        struct Node // class and struct is intrinsically same, except for private member & public readable
        {
            elemType data;
            Node *next;
            Node(const elemType &x, Node *n = NULL)
                {data = x; next = n;}
            // Node(void):next(NULL){} /* not necessary because we do not need head node for stack*/
            ~Node(){}
        };
        Node *Top; // a_0 saved at last node
    public:
        LinkStack(void);
        ~LinkStack();

        bool isEmpty(void) const;
        elemType top(void) const;
        elemType pop(void);
        void push(const elemType &x);
};

/* initialization of sequential stack -> empty*/
template <class elemType>
LinkStack<elemType>:: LinkStack(void)
{
    Top = NULL;
}

/* double pointer method*/
template <class elemType>
LinkStack<elemType>:: ~LinkStack()
{
    Node *tmp;
    while(Top)
    {
        // subsequently "pull" the successor
        tmp = Top;
        Top = Top->next;
        delete tmp;
    }
   
}


template <class elemType>
bool LinkStack<elemType>:: isEmpty(void) const
{
    return (!Top);
}


template <class elemType>
elemType LinkStack<elemType>:: top(void) const
{
    if(!Top) throw OutOfBound();
    return Top->data;
}

template <class elemType>
elemType LinkStack<elemType>:: pop(void)
{
    // not necessary, checked by user: isEmpty as loop condition
    if(!Top)   throw OutOfBound();
    Node *tmp  = Top;
    elemType x = Top->data;
    Top        = Top->next;
    delete tmp;
    return x;
}

// worst: O(n) complexity due to doubleSpace; O(1) average;
template <class elemType>
void LinkStack<elemType>:: push(const elemType &x)
{
    Node *tmp = new Node(x, Top);
    Top = tmp;
}
