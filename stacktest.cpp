#include "SeqStack.hpp"
#include "LinkStack.hpp"

int main(void)
{
    SeqStack<int> s1;
    LinkStack<double> s2;   

    for(int i=0; i<10;i++)
    {
        s1.push(i);
        if(i%2==0)
            cout << s1.pop() << endl;
        else
            cout << s1.top() << endl;
    }

    for(int i=0; i<10;i++)
    {
        s2.push((double)i * 7.2);
    }

    cout << "---s1---" << endl;
    while(!s1.isEmpty())
        cout << s1.pop()<<endl;

    cout << "---s2---" << endl;
    while(!s2.isEmpty())
        cout << s2.pop()<<endl;

    cout << "here:" <<endl;
    char tmps = 'o';
    while(tmps!='\n')
        cin >> tmps;
    cout << "there" << endl;
    return 0;
}