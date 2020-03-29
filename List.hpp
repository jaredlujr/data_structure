#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif


/* ERROR type definition*/
class OutOfBound: public exception
{
    const char *what(void) const throw() // what is the common method of exception class, it return the cause of error
    {
        return "[ERROR]Your visit is out of the maximum size of list!\n";
    }
};

class IllegalSize: public exception
{
    const char *what(void) const throw()
    {
        return "[ERROR]Allocating memory failed.Illegal Size arises!\n";
    }
};


/* BASE CLASS where virtual functions are defined*/
template <class elemType>
class List
{
    public:
        // basic operations of arbitrary list implementation
        virtual int length() const = 0; //get the length of list, read-only
        virtual int index(const elemType &x)  const = 0; // get the first index of specific element, read-only
        virtual elemType visit(int i)   const = 0; // same as operator [], read-only
        virtual void insert(int i, const elemType &x) = 0; //insert new element=x at index=i
        virtual void remove(int i) = 0; //remove the element present with index=i
        virtual void clear(void) = 0; // setting the length into zero; THIS IS NOT DELETE.
        virtual void traverse(void) const = 0; //traverse the whole list, read-only
        virtual ~List(void) {};
};
