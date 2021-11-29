#include <iostream>
#include <vector>
#include <algorithm>

class X  
{
public :
    int key ,val;
    X(int k , int v)
       : key{k} , val{v}
    {

    }
    bool operator > (const X& r) const
    {
        return (val > r.val) ;
    }
};

int main()
{
    std::vector <X> vec;
    vec.push_back(X(1,4));
    vec.push_back(X(2,3));
    vec.push_back(X(3,5));
    vec.push_back(X(4,1));
    std::sort(vec.begin(),vec.end(),std::greater<X>());
    for(auto& v : vec)
    {
        std::cout << v.val << ' ';
    }
}

// class MyStruct
// {
// public :
//     int key;
//     std::string stringValue;

//     MyStruct(int k, const std::string& s) : key(k), stringValue(s) {}

//     bool operator > (const MyStruct& str) const
//     {
//         return (key > str.key);
//     }
// };

// int main()
// {
//     std::vector < MyStruct > vec;
//     vec.push_back(MyStruct(1, "test"));
//     vec.push_back(MyStruct(3, "is"));
//     vec.push_back(MyStruct(2, "a"));
//     vec.push_back(MyStruct(4, "this"));
//     std::sort(vec.begin(), vec.end(),std::greater<MyStruct>());
//     for(auto& s : vec)
//     {
//         std::cout << s.stringValue;
//     }
// }