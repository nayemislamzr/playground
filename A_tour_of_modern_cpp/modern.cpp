#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <numeric>
#include <vector>

/*
** C++ algorithm library
*/

/*
    All of -  returns true for all elements in the range [first, last).
    any of - returns true for at least one element in the range [first, last).
    none of - returns true for no elements in the range [first, last).
*/

// int main() {
//     std::vector<int> a(10) ;
//     int itr = 0 ;
//     for(auto& val : a) {
//         itr+=2;
//         val = itr ;
//     }
//     //a { 2, 4 , 6 , ...}
//     if(std::all_of(std::cbegin(a), std::cend(a) , [](int i) { return !(i%2) ;})) {
//         std::cout << "All numbers are even\n" ;
//     }
//     a.push_back(11);
//     // a { 2, 4, 6 ,... , 11}
//     if(std::any_of(std::cbegin(a), std::cend(a) , [](int i) { return (i%2) ;})) {
//         std::cout << "Atleast one odd number found!\n" ;
//     }
//     a.pop_back();
//     //a { 2, 4 , 6 , ...}
//     if(std::none_of(std::cbegin(a), std::cend(a) , [](int i) { return (i%2) ;})) {
//         std::cout << "No odd number found!\n" ;
//     }
// }


/*
    partial sum (_start , _end , _result)- accumulates (sums) the value in the range [start,end] then 
    saves it to _result
*/

// int main() {
//     std::vector<int> vec (10,1);
//     std::vector<int> another_vec(10);
//     std::partial_sum(std::begin(vec) , std::end(vec) , std::begin(another_vec));
//     for(auto& val : another_vec) {
//         std::cout << val << " ";
//     }
// }

/*
    for_each_n - basically for_each with range size rather then two pointer
*/

// int main() {
//     std::vector<int> vec(10,1);
//     std::for_each_n(vec.begin() , 5 , [](int& val){static int itr{0} ; val = ++itr;});
//     std::for_each_n(vec.begin() , 10 , [](int& val){std::cout << val << " ";});
//     return 0;
// }

/*
    count - (_start , _end , _target_value)
    count_if -(start , end , p) counts elements for which predicate p returns true.
*/

// int main() {
//     std::vector<int> vec {3,6,3,5,3,10,15} ;
//     int no_of_three_in_vec = std::count(vec.begin() , vec.end() , 3);
//     std::cout << "No of three : " << no_of_three_in_vec << '\n' ;
//     int numbers_divisible_by_three = std::count_if(vec.begin() , vec.end() , [](int& i) { return !(i%3);});
//     std::cout << "# of Numbers divisible by three : " << numbers_divisible_by_three << '\n' ;
//     return 0;
// }

/*
    mismatch
*/

// int main() {
//     std::string str1 = "Hello ,Jorina" ;
//     std::string str2 = "Hello ,Morzina" ;
//     std::cout << std::string(str1.begin(),std::mismatch(str1.begin(),str1.end(),str2.begin()).first);
// }

/*
    Find
    Find if
    Find if not
*/

// int main() {
//     std::vector<int> vec {1,43,45,4,6,5,433,3432,523,4,5,343,54,23};
//     if(std::find(vec.begin(),vec.end(), 343) != vec.end()) {
//         std::cout << "343 is present in vec\n" ;
//     }
//     auto itr = std::find_if(vec.begin(),vec.end(),[](int& i){return !(i%2);});
//     std::cout << "First occurence of even number : " << *itr << '\n' ;
//     itr = std::find_if_not(vec.begin(),vec.end(),[](int& i){return (i%2);});
//     std::cout << "First occurence of even number : " << *itr << '\n' ;
//     return 0;
// }

/*
    find end - find sequence
*/

// int main() {
//     std::vector<int> v{1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
//     std::vector<int> t1{4};
//     auto result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
//     if (result == v.end()) {
//         std::cout << "sequence not found\n";
//     } else {
//         std::cout << "last occurrence is at: "
//                   << std::distance(v.begin(), result) << "\n";
//     }
// }

/*
    std::move
*/

// int main() {
//     std::vector<int> vec1 {1,2,3,4,5,6,7,8,9};
//     std::vector<int> vec2(10);
//     std::move(vec1.begin(),vec1.end(),vec2.bac);
//     for(auto& val : vec2) {
//         std::cout << val << " ";
//     }
// }

// [[nodiscard]] constexpr int sum(int a , int b) { return a+b ;}

// int main() {
//     int totalSum = sum(1,2);
//     return 0;
// }