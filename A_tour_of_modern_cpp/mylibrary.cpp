#include <iostream>
#include <vector>

template<typename T>
constexpr void do_double(T& value) noexcept{
    value*=2;
}

template<typename Container , typename Function>
void for_each(Container&& container , Function f) {
    auto start_with = std::begin(container);
    auto end_with = std::end(container);
    while(start_with!=end_with) {
        f(*start_with);
        ++start_with ;
    }
}

int main() {
    std::vector<int>a(10);
    int itr = 0 ;
    for(auto& val : a){
        val = ++itr ;
    }
    for_each(a,do_double<int>);
    for(auto& val : a){
        std::cout << val << " ";
    }
}