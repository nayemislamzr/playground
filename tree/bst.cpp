#include <iostream>

class BST
{
    private :
        int64_t data;
        BST *right, *left;
    public :
        BST()
            : data{0},right{nullptr},left{nullptr}
        {

        }
        BST(int val)
            : data{val},right{nullptr},left{nullptr}
        {

        }
        BST* Insert(BST* root , int64_t key)
        {
            if(!root)
                return new BST(key);
            if(key > root->data)
                root->right = Insert(root->right, key);
            else
                root->left = Insert(root->left, key);
            return root;
        }
        BST* Inorder_successor(BST* root)
        {
            BST* current_node = root;
            while (current_node && current_node->left != NULL)
                current_node = current_node->left;
            return current_node;
        }
        BST* Delete(BST* root, int64_t key)
        {
            if (root == NULL)
                return root;
            if (key > root->data)
                root->right = Delete(root->right, key);
            else if (key < root->data)
                root->left = Delete(root->left, key);
            else
            {
                if(root->left == NULL && root->right == NULL)
                    return NULL;
                else if(root->left == NULL)
                {
                    BST* temp = root->right;
                    free(root);
                    return temp;
                }
                else if(root->right == NULL)
                {
                    BST* temp = root->left;
                    free(root);
                    return temp;
                }
                else
                {
                    BST* temp = Inorder_successor(root->right);
                    root->data = temp->data;
                    root->right = Delete(root->right,temp->data);
                }
            }
            return root;
        }
        BST* Search(BST* root, int key)
        {
            if(root == NULL, root->data == key)
                return root;
            if(key > root->data)
                Search(root->right, key);
            else 
                Search(root->left,key);
        }
        void Inorder(BST* root)
        {
            if(root == NULL)
                return;
            Inorder(root->left);
            std::cout << root->data << ' ';
            Inorder(root->right);
        }
};

int main()
{
    BST b, *root = NULL;
    root = b.Insert(root, 50);
    b.Insert(root, 30);
    b.Insert(root, 20);
    b.Insert(root, 40);
    b.Insert(root, 70);
    b.Insert(root, 60);
    b.Insert(root, 80);
    b.Delete(root,70);
    b.Inorder(root);
}