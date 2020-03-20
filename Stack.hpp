#ifndef IOSTD
    #define IOSTD
    #include <iostream>
    using namespace std;
#endif


/* abstract class*/
template <class elemType>
class stack
{
    public:
        virtual bool isEmpty(void) const = 0;
        virtual elemType top(void) const = 0;
        virtual void push(const elemType &x) = 0;
        virtual elemType pop(void) = 0;
        virtual ~stack(){}
};

