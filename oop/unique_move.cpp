#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class myClass
{
private :
    std::unique_ptr<std::vector<int>> root;
public :
    myClass()
        : root {new std::vector<int> (5)}
    {
        fill(root->begin(),root->end(),5);
    }

    myClass(myClass& right)
        : root{new std::vector<int> (*right.root)}
    {
        std::cout << "copied" ;
    }

    myClass(myClass&& right)
        : root{std::move(right.root)}
    {
        std::cout << "moved";
    }

};

int main()
{   
    // std::unique_ptr<std::vector<int>> oldObj;
    // oldObj = std::unique_ptr<std::vector<int>> (new std::vector<int> (5));
    // fill(oldObj->begin(),oldObj->end(),5);
    // std::unique_ptr<std::vector<int>> newObj(std::move(oldObj));
    // std::for_each(newObj->begin(),newObj->end(),[](int v){std::cout << v;});

    myClass a;
    myClass b(std::move(a)); 

}