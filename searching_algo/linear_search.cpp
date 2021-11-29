#include <iostream>
#include <vector>

/*
    How this works:
    iterate from beginning to the end of the array and compares the current element with 
    searched element if it finds a match the search is terminated.

    Time complexity:
    *Best case : 0(1) - finds the element at the first index
    *Worst case : 0(n) - finds the element at the last index
    *Average case : 0(n)

*/

bool linear_search(std::vector<int>& number, int search_element)
{
    for(auto& n : number)
    {
        if(n == search_element)
            return true;
    }
    return false;
}

int main()
{
    std::vector<int> numbers = {5,7,2,10,8,15,78,34,23,66,44,23,5};
    int searched_element;
    std::cin >> searched_element;
    if(linear_search(numbers,searched_element))
        std::cout << "Found!!!" << std::endl;
    else std::cout << "Not Found!!!" << std::endl;
}