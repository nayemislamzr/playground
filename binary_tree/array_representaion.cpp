#include <iostream>
#define SIZE 100

/*
    Binary Tree - Tree with not more thean 2 childs

    if (parent == p) using 0 indexing
    left subtree = 2*p+1
    right subtree = 2*p+2

    if child = c using 0 indexing
    parent = (c-1)/2
*/

class binary_tree
{
    int bt[SIZE];
public:
    binary_tree() = default;
    void addLeftChild(int parent, int child)
    {
        bt[2*parent + 1] = child;
    }
    void addRightChild(int parent, int child)
    {
        bt[2*parent + 2] = child;
    }
};