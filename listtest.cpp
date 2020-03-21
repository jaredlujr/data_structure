#include "SeqList.hpp"
#include "LinkList.hpp"
#include "DlinkList.hpp"

/* easy test*/
int main(void)
{
    DlinkList<double> list;
    double d1=3.1;
    double d2=4.5;

    list.insert(0,d1);
    list.insert(0,d2);
    list.insert(0,d1);
    
    cout << list.visit(0) << " "<< list.visit(1) <<endl;
    
    cout << "len: "<< list.length() <<endl;
    list.traverse();
    list.clear();
    return 0;

}
