#include <iostream>
#include <memory>
#include <vector>

namespace simple_DS {
    
    using namespace std;
    
    struct node {
        // protected :
        public :
        int val;
        int height;
        node  *left, *right ;
        
        public:
        node() = default;
        node(int key) 
            : val {key} , height{1} , left{NULL} , right{NULL} {

        }
        ~node() = default ;
        // friend class AVLTree ;
    };

    class AVLTree : public node {
        // private :
        public :
        node* root ;

        public :
        AVLTree() 
            : root{NULL} {
            cout << "Created an AVL Tree :)\n" ;
        }
        ~AVLTree() {
            cout << "Destroyed an AVL Tree :(\n" ;
        }

        private :
        int get_height(node* p_node);
        int get_balance(node* p_node);
        node* in_order_successor(node* p_node);
        node* right_rotate(node* p_node);
        node* left_rotate(node* p_node);
        
        public :
        node* insert_node(node* temp_node , int key);
        node* delete_node(node* temp_node , int key);
        void pre_order(node* p_node);
    };

    int AVLTree::get_height(node* p_node) {
        if(!p_node)
            return 0;
        return p_node->height ;
    }

    int AVLTree::get_balance(node* p_node) {
        if(!p_node)
            return 0;
        return get_height(p_node->left) - get_height(p_node->right);
    }

    node* AVLTree::in_order_successor (node* p_node) {
        node* temp_node = p_node ;
        while(temp_node->left) {
            temp_node = temp_node->left ;
        }
        return temp_node ;
    }

    node* AVLTree::right_rotate(node* p_node) {
        node* left_node = p_node->left ;
        node* right_node = p_node->right ;

        left_node->right = p_node ;
        p_node->left = right_node ;

        left_node->height = max(get_height(left_node->left),get_height(left_node->right)) + 1;
        p_node->height = max(get_height(p_node->left), get_height(p_node->right)) + 1;

        return left_node ;
    }

    node* AVLTree::left_rotate(node* p_node) {
        node* left_node = p_node->left ;
        node* right_node = p_node->right ;

        right_node->left = p_node ;
        p_node->right = left_node ;

        right_node->height = max(get_height(right_node->left), get_height(right_node->right)) + 1;
        p_node->height = max(get_height(p_node->left), get_height(p_node->right)) + 1 ;

        return right_node;
    }

    node* AVLTree::insert_node(node* temp_node , int key) {
        if(temp_node == NULL) 
            return (new node(key));

        if(key < temp_node->val)
            temp_node->left = insert_node(temp_node->left , key) ;
        else if(key > temp_node->val)
            temp_node->right = insert_node(temp_node->right , key);
        else return temp_node ;

        temp_node->height = max(get_height(temp_node->left), get_height(temp_node->right)) + 1;

        int balance = get_balance(temp_node) ;
        // Left Left case
        if(balance > 1 and key < temp_node->left->val)
            return right_rotate(temp_node);    
        // Right Right case
        if(balance < -1 and key > temp_node->right->val)
            return right_rotate(temp_node);
        // Left Right case
        if(balance > 1 and key > temp_node->left->val) {
            temp_node->left = left_rotate(temp_node->left);
            return right_rotate(temp_node);
        }
        // Right Left case
        if(balance < -1 and key < temp_node->right->val) {
            temp_node->right = right_rotate(temp_node->right);
            return left_rotate(temp_node);
        }
        return temp_node;
    
    }

    node* AVLTree::delete_node(node* temp_node , int key) {
        if(!temp_node)
            return temp_node;
        
        if(key < temp_node->val)
            temp_node->left = delete_node(temp_node->left , key);
        else if(key > temp_node->val)
            temp_node->right = delete_node(temp_node->right , key);
        else {
            if(!temp_node->left or !temp_node->right) {
                node *temp = temp_node->left ? temp_node->left : temp_node->right;

                if(!temp)
                {
                    temp = temp_node;
                    temp_node = NULL;
                }
                else temp_node = temp;
                delete temp;
            }
            else {
                node *temp = in_order_successor(temp_node->right);

                temp_node->val = temp->val;

                temp_node->right = delete_node(temp_node->right, temp->val);
            }
        }
    
        if(!temp_node) return temp_node;

        root->height = 1 + max(get_height(temp_node->left), get_height(temp_node->right));

        int balance = get_balance(temp_node);

        //Left Left Case
        if(balance > 1 and get_balance(temp_node->left) >= 0)
            return right_rotate(temp_node);

        //Left Right Case
        if(balance > 1 and get_balance(temp_node->left) < 0) {
            temp_node->left = left_rotate(temp_node->left);
            return right_rotate(temp_node);
        }

        //Right Right Case
        if(balance < -1 and get_balance(temp_node->right) <= 0)
            return left_rotate(temp_node);

        //Right Left Case
        if(balance < -1 and get_balance(temp_node->right) > 0) {
            temp_node->right = right_rotate(temp_node->right);
            return left_rotate(temp_node);
        }

        return temp_node;

    }

    void AVLTree::pre_order(node *x) {
        if(x) {
            cout << x->val << " ";
            pre_order(x->left);
            pre_order(x->right);
        }
    }

}



int main() {
    simple_DS::AVLTree t, p;

    std::vector<int> v {9, 5, 10, 0, 6, 11, -1, 1, 2};

    for(int i=0; i<9; i++)
        t.root=t.insert_node(t.root, v[i]);

    std::cout << "traversal\n";
    t.pre_order(t.root);
    std::cout << '\n';

    t.root = t.delete_node(t.root, 10);

    t.pre_order(t.root);
    std::cout << '\n';

    return 0;
}