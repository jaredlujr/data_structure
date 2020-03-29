/*
Application of stack:
    TO DESCRIBE A STACK-LIKE PROBLEM, like function call.

    GOAL: Use stack to simulate the operation of expression evaluation.  At most + - * / and parenthesis () involed
 */

#include "SeqStack.hpp"
#include "LinkStack.hpp"


// input: sufstring including 0-9 + _ * /, parenthesis-free 
// data type: integer 0-9
int calcPost(char *sufStr)
{
    int opleft,opright,op;
    int tmp,i;
    LinkStack <int> s;

    i = 0;
    while(sufStr[i]!='\0')
    {
        if( (sufStr[i] >= '0') && (sufStr[i] <= '9') ) // 1-digit integer 
        {
            tmp = sufStr[i] - '0';
            s.push(tmp); // push into stack
        }
        else // operator case
        {
            // pop the operands, right operand at top
            opright = s.pop();
            opleft  = s.pop();

            switch(sufStr[i])
            {
                case '*': op = opleft * opright; break;
                case '/': op = opleft / opright; break;
                case '+': op = opleft + opright; break;
                case '-': op = opleft - opright; break;
                default: break;
            };
            s.push(op);
        }
        i++;
    }
    op = s.pop(); // the last operand, say result
    return op;
}

// in-expression transformation into suf-expression, as string
// read is sequential 
void inTosuf(char *inStr, char *sufStr)
{
    LinkStack<char> s; //using operator stack
    int i,j;
    char topCh, hash = '#';

    s.push(hash); // like head node in linklist, to unify the process
    i = 0;j = 0;
    while(inStr[i]) // also as ` inStr[i]!='\0' ` 
    {
        if( (inStr[i] >= '0') && ( inStr[i] <= '9') )// operand: output directly
            sufStr[j++] = inStr[i++]; 
        else // operator
        {
            switch(inStr[i]) // for one time, only one char shifted
            {
                case '(': s.push(inStr[j]); break;
                case ')': 
                {
                    topCh = s.pop(); // print-free for '('
                    while(topCh!='(')
                    {
                        sufStr[j++] = topCh;
                        topCh = s.pop();
                    }
                    break;
                }
                case '*': s.push(inStr[i]); break;
                case '/': s.push(inStr[i]); break;
                case '+':
                {
                    topCh = s.top(); // print the last operator
                    while( (topCh == '*') or (topCh == '/') )
                    {
                            sufStr[j++] = s.pop();
                            topCh = s.top();
                    }
                    s.push(inStr[i]);
                    break;
                }
                case '-':
                {
                    topCh = s.top(); // print the last operator
                    while( (topCh == '*') or (topCh == '/') )
                    {
                            sufStr[j++] = s.pop();
                            topCh = s.top();
                    }
                    s.push(inStr[i]);
                }
                default: break;
            }
            i++;
        }
    }
    
    while(s.top() != hash)
        sufStr[j++] = s.pop();
    
}




int main(void)
{
    char *express = new char[20];
    char *target = new char[20];
    cout << "Pleanse input an expression without space(only[0-9],+_*/() can be included)!:" << endl;
    cin >> express;
    inTosuf(express, target);
    cout << target << endl;
    cout << calcPost(target) << endl;
    return 0;

}