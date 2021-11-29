// #include <iostream>
// #include <memory>
// #include <utility>

// template <typename T1 , typename T2>
// class pair {
// public :
//     T1* first ;
//     T2* second ;
// public :
//     pair(T1 firstData , T2 secondData) {
//         std::cout << "Initilized!\n" ;
//         first = new T1 ;
//         second = new T2 ;
//         *first = firstData ;
//         *second = secondData ;
//     }
//     pair(const pair& other) {
//         std::cout << "Copied!\n" ;
//         first = new T1 ;
//         second = new T2 ;
//         *first = *(other.first) ;
//         *second = *(other.second) ;
//     }
//     pair(pair&& other) noexcept
//         : first {std::move(other.first)} , second {std::move(other.second)} {
//         std::cout << "Moved!\n" ;
//     }
//     // ~pair() {
//     //     free(first);
//     //     free(second);
//     // }
// };

// int main() {
//     pair<int , int> hello(12,32);
//     pair<int , int> world = hello ;
//     pair<int , int> gaming (std::move(hello));
//     std::cout << *hello.first << " " << *hello.second << '\n' ;
//     std::cout << *world.first << " " << *world.second << '\n';
//     std::cout << *gaming.first << " " << *gaming.second << '\n' ;
// }

// #include <iostream>
// #include <memory>

// class Move {
// private :
//     int* data ;
// public :
//     Move(int d) {
//         std::cout << "Initialized!\n" ; 
//         data = new int ;
//         *data = d ;
//     }
//     explicit Move(Move&& other) noexcept
//         : data{other.data} {
//         std::cout << "Moved\n" ;
//         other.data = nullptr ;
//     }
//     void print() {
//         std::cout << *data << '\n' ;
//     }
//     ~Move() {
//         free(data);
//     }
// };

// int main() {
//     Move hello(Move {2});
//     return 0;
// }

// #include <iostream>
// #include <vector>

// using namespace std;
 
// std::vector<int> doubleValues (vector<int>& v)
// {
//     for(auto& value : v) {
//         value *= 2 ;
//     }
//     return v;
// }
 
// int main()
// {
//     std::vector<int> v(100);
//     for(uint32_t i = 0 ; i < 100 ; i++) {
//         v[i] = i ;
//     }    
//     std::vector<int> &x = doubleValues(v) ;
//     for(auto& value : v) {
//         std::cout << value << " ";
//     }
//     return 0;
// }

// #include <iostream>
// #include <cassert>

// class hey {
// private :
//     int* d ;
// public :
//     hey(int data) {
//         std::cout << "constructed!\n" ;
//         d = new int ;
//         *d = data ;
//     }
//     hey(const hey& other) {
//         std::cout << "copied!\n" ;
//         d = new int ;
//         *d = *other.d ;
//     }
//     hey(hey&& other)
//         : d{other.d} {
//         std::cout << "moved!\n" ;
//         other.d = NULL ;
//     }
//     ~hey() {
//         std::cout << "destructed!\n" ;
//         delete d;
//     }
// };

// hey bobby() {
//     return hey(2) ;
// }

// int main() {
//     hey y(2) ;
//     assert(y==2);
//     return 0;
// }

// #include <iostream>

// class Karma {
// public :
//     Karma(const int& d) {
//         std::cout << "lvalue reference!\n" ; 
//     }
//     Karma(int&& d) {
//         std::cout << "rvalue reference!\n" ;
//     }
// };


// int main() {
//     int x = 3 ;
//     Karma y(x);
//     Karma z(3);
//     return 0;
// }

// #include <iostream>

// class ArrayWrapper
// {
// public:
//     // default constructor produces a moderately sized array
//     ArrayWrapper ()
//         : _p_vals( new int[ 64 ] )
//         , _size( 64 )
//     {}
 
//     ArrayWrapper (int n)
//         : _p_vals( new int[ n ] )
//         , _size( n )
//     {
//         std::cout << "constructed!\n" ;
//         for(uint32_t i = 0 ; i < _size ; i++) {
//             _p_vals[i] = i+1 ;
//         }
//     }
 
//     // move constructor
//     ArrayWrapper (ArrayWrapper&& other)
//         : _p_vals( other._p_vals  )
//         , _size( other._size )
//     {
//         std::cout << "moved!\n" ;
//         other._p_vals = nullptr;
//         other._size = 0;
//     }
 
//     // copy constructor
//     ArrayWrapper (const ArrayWrapper& other)
//         : ArrayWrapper(other._size)
//     {
//         std::cout << "copied!\n" ;
//         for ( int i = 0; i < _size; ++i )
//         {
//             _p_vals[ i ] = other._p_vals[ i ];
//         }
//     }

//     void operator= (const ArrayWrapper& other) {
//         delete[] _p_vals ;
//         std::cout << "copied!\n" ;
//         _p_vals = new int[other._size];
//         _size = other._size ;
//         for ( int i = 0; i < _size; ++i )
//         {
//             _p_vals[ i ] = other._p_vals[ i ];
//         }
//     }

//     void show() {
//         for(uint32_t i = 0 ; i < _size ; i++) {
//             std::cout << i << " " ;
//         }
//         std::cout << '\n' ;
//     }

//     ~ArrayWrapper ()
//     {
//         std::cout << "destructed!\n" ;
//         delete [] _p_vals;
//     }
    
// private:
//     int *_p_vals;
//     int _size;
// };

// ArrayWrapper move() {
//     return ArrayWrapper(4);
// }

// int main() {
//     ArrayWrapper x(5);
//     move() = x ;
//     move().show();
// }

// #include <iostream>
// #include <memory>

// class Holder {
// private :
//     std::unique_ptr<std::string> m_data ;
//     int m_size ;
// public :
//     Holder(std::string_view other) {
//         m_data.reset(new std::string);
//         *m_data.get() = other ; 
//         m_size = other.size();
//     }
//     void print() {
//         std::cout << *m_data.get() ;
//     }
// };
// int main() {
//     int a = 10 , b = 5;
//     int c = std::exchange(a , b);
//     std::cout << &a << " " << &b << " " << &c ;
//     return 0;
// }

#include <iostream>
#include <utility>

int main() {
    int x = std::forward(2);
}