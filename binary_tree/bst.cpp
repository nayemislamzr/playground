#include <iostream>

struct node
{
    int data;
    node *left,*right;
    node() = default;
    node(int val)
        : data {val},left {nullptr} ,right {nullptr}
    {

    }
};

class BST
{
    node* root = nullptr;
public :
    BST()
    { 

    }
    node* insert(int val,node* m_root)
    {
        if(root == nullptr)
            return new node(val);
        if(val > root->data)
            m_root->right = insert(val,m_root->right);
        else m_root->left = insert(val,m_root->left);
        return m_root;
    }
    node 
};