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


/* abstract class*/
template <class elemType>
class Stack
{
    public:
        virtual bool isEmpty(void) const = 0;
        virtual elemType top(void) const = 0;
        virtual void push(const elemType &x) = 0;
        virtual elemType pop(void) = 0;
        virtual ~Stack(){};
};

