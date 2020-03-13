
#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif

#ifndef LIST
    #define LIST
    #include "List.hpp"
#endif

/* This is source code for implementation of link list, 
    utilize the templated class with some member functions */


// link list declaration
template <class elemType>
class LinkList: public List <elemType>
{
    private:
        struct Node
        {
            elemType data;
            Node *next;
            // initialization function: 2 cases
            Node(const elemType &x, Node *p = NULL)
                {data = x; next = p;}
            Node():next(NULL){}

            ~Node(){};
        };
        Node *HEAD;// head Node, with no data stored
        int currentLength; // for convenience
    public:
        LinkList(void); //construction
        ~LinkList(){clear(); delete HEAD;} //deconstruction, data is allocated from heap
        int length(void) const;
        int index(const elemType &x)  const;
        elemType visit(int i)  const;
        void insert(int i, const elemType &x);
        void remove(int i);
        void clear(void); // free all the non-head Node
        void traverse(void) const;
};


/* Specific member functions of LinkList*/

template <class elemType>
LinkList <elemType>:: LinkList(void)
{
    HEAD = new Node(); // allocate an empty HEAD-linkNode and let head point to it
    currentLength = 0; //counting initialization, HEAD is not included
}

template <class elemType>
int LinkList <elemType>:: length(void) const
{
    return currentLength;
}

/* for link list, the index also starts from "0" as the 1st linkNode */
template <class elemType>
int LinkList <elemType>:: index(const elemType &x) const
{
    int count = 0;
    Node *p = HEAD->next; // now p is at 1st Node(if not NULL)
    while(p)
    {
        if(p->data == x) return count;
        p = p->next;
        count++;
    }
    return -1;
}

template <class elemType>
elemType LinkList <elemType>:: visit(int i) const
{
    int j = 0;
    Node *p = HEAD->next;
    for(j=0;j<i;j++)
       p = p->next;
    
    return p->data;
}

template <class elemType>
void LinkList <elemType>:: insert(int i, const elemType &x)
{
    if(i> currentLength || i< 0)// check it
    {
        throw OutOfBound();
        return;
    }

    int j = 0;
    Node *p = HEAD;
    for(j=0;j<i;j++)
       p = p->next;

    Node *tmp = new Node();
    tmp->data = x;
    tmp->next = p->next;
    p->next = tmp;
    //update
    currentLength++;
}

template <class elemType>
void LinkList <elemType>:: remove(int i)
{
    if(i>= currentLength || i< 0)// check it
    {
        throw OutOfBound();
        return;
    }

    int j = 0;
    Node *p = HEAD;
    for(j=0;j<i;j++)
       p = p->next;

    Node *tmp = new Node();
    tmp = (p->next)->next;
    delete p->next;
    p->next = tmp;
    //update
    currentLength--;

}

template <class elemType>
void LinkList <elemType>:: clear(void)
{
    Node *p = HEAD->next;
    Node *tmp;
    HEAD->next = NULL;
    while(p)
    {
        tmp = p;
        p = p->next;
        delete tmp;
    }

}

template <class elemType>
void LinkList <elemType>:: traverse(void) const
{
    Node *p = HEAD->next;
    cout << "[";
    while(p)
    {
        cout << p->data<< " ";
        p = p->next;
    }
    cout << "]" << endl;
}

