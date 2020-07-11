#include "BinaryTree.hpp"

int main(void)
{
    BinaryTree<int> T;
    //T.createTree(-1);
    //T.buildTree();
    int i,n;
    cin >> n;
    int *post = new int[n];
    int *in = new int[n];
    for(i=0;i<n;i++)
        cin >> in[i];
    for(i=0;i<n;i++)
        cin >> post[i];

    T.createFromRoot(T.buildFromInPost(in,0,n-1,post,0,n-1));
    
    T.PreOrder_nr();

    return 0;
}