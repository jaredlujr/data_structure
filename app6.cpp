#include "binary_tree.hpp"


/* 
    Given Expression Tree, to calculate the result of it
    Number range[0-9]
    Input:  <Node *> in tree, address // pointer
            Node.data -> single char
    Output: <int>
    --> PostOrder
*/




int main(void)
{
    BinaryTree<char> tree;
    tree.createTree('#');
    cout << tree.calcExpression()<<endl;
    return 0;
}
