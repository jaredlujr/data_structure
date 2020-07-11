/*
enter some number of characters and push them into one seqlist,
delete the first node and insert it into the medium position
a bcdefg -> bcd a efg    
An simple application of sequential list and linked list
*/


// #include "SeqList.hpp" 
#include "link_list.hpp"

// 

int main(void){

    //SeqList<char> ch_list(21); // 21 = 1(index=0) + 20(the rest nodes)
    LinkList<char> ch_list;

    char ctmp;
    int i,n,result;

    // enter the length of the input string
    cout << " Number of the elements: "<<endl;
    cin >> n;
    cin.get(ctmp); // throw away the input from buffer

    cout << "input the elements now:" << endl;
    // push the char into ch_list ( to rear )
    for(i=0;i<n;i++)
    {
        cin.get(ctmp);
        ch_list.insert(i,ctmp);
    }

    ctmp = ch_list.visit(0); // obtain the value of first node
    ch_list.remove(0);
    ch_list.insert(ch_list.length()/2, ctmp);// get the index of medium and insert

    cout << "output the elements now:"<<endl;
    ch_list.traverse();
    
    return 0;
}
