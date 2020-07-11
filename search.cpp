
#include <iostream>

using namespace std;

// HW week 10

// Toy one, only int as value (distinct)
class BinarySearchTree
{
    private:
        struct BinaryNode
        {
            int value;
            BinaryNode *left;
            BinaryNode *right;
            BinaryNode(const int &x,BinaryNode *lt=NULL,BinaryNode *rt=NULL): value(x), left(lt), right(rt){}
        };
        BinaryNode *root;
    public:
        void insert(const int &x);
        BinarySearchTree(){root=NULL;}
        ~BinarySearchTree(){};
};


void BinarySearchTree:: insert(const int &x)
{
    if(!root)
    {
        root = new BinaryNode(x);
        cout <<  "-1" << endl;
        return;
    }
    BinaryNode *p = root;
    // Non-recursive insert
    
    while(p)
    {   
        if(x == p->value) return; // impossible case, but safe
        else if(x < p->value)
        {
            if(!(p->left))// empty, insert allowed
            {
                p->left = new BinaryNode(x);
                cout<<  p->value << endl;
                return;
            }
            p = p->left; // shift
        }
        else
        {
            if(!(p->right))
            {
                p->right = new BinaryNode(x);
                cout<<  p->value << endl;
                return;
            }
            p = p->right;
        }//if
    }//while
    
}


int main(void)
{
    int i,n,x;
    cin >> n;
    BinarySearchTree t;
    for(i=0;i<n;i++)
    {
        cin >> x;
        t.insert(x);
    }
    return 0;
}