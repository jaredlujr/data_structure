/*
Application of stack:
    Raliway station management.
 */

#include "SeqStack.hpp"

/*main function*/

int main(void)
{
    int t,i;
    cin >> t;
    int *result = new int[t];
    int *a;

    for(i=0;i<t;i++) // where management happens
    {
        int m,n;
        int j, curr_t; 
        int flag = 1;

        cin >> n >> m;

        SeqStack<int> s;

        int length = 0, pt = 0;
        
        a = new int[n]; // source, can also be stack
        
        for(j=0;j<n;j++)
            a[j] = j;

        s.push(a[pt++]); // first push, pt points to the first unmanaged car
        length++; // record the length of STACK
        
        // to "find" each element sequentially
        
        for(j=0;j<n;j++)
        {
            int iflag = 1;
            cin >> curr_t; // to be departed
            
            //cout << curr_t <<endl; /* debug*/
            
            while(s.top()!=curr_t)
            {
                if(length==(m+1) or (pt==n) ) // boundary condition: use up stack or source
                {
                    iflag = 0;
                    break; // exit while
                }
                s.push(a[pt++]); // push in and continue finding
                length++;
            }

            if(iflag==0) // find failure exist, exit, marked as NO
            {
                flag=0; 
            }
            else
            {
                 s.pop(); // find it ! continue
                // cout << s.pop()<<endl; /* debug */
                length--;
            }
        }
        if(flag==0)
            result[i] = 0;
        else
            result[i] = 1;
        delete[] a;
    }


    for(i=0;i<t;i++)
    {
        if(result[i] == 0)
            cout<< "NO" << endl;
        else
            cout << "YES" << endl;
    }
    delete[] result;
    return 0;
}