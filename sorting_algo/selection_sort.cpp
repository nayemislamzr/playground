#include <iostream>
#include <vector>

/*
    How this works:
    Selection sort maintains two subarrays in given form:
    (i) One subarray which is unsorted
    (ii) other one which is sorted
    In each iteration selection sort picks the min element from the 
    unsorted array then adds this to the sorted array

    Time complexity:
    *Best case : 0(n) - when the array is already sorted
    *Worst case : 0(n*n) - when the array is reversely sorted
    *Average case : 0(n*n)

    Auxiliary space : 0(1)
*/

void selection_sort(std::vector<int>& numbers)
{
    for(int i = 0 ; i < numbers.size() ; i++)
    {
        int small = i;
        for(int j = i + 1 ; j < numbers.size() ; j++)
        {
            if(numbers[j] < numbers[small])
                small = j;
        }
        std::swap(numbers[small],numbers[i]);
    }
}

int main()
{
    std::vector<int> numbers = {5,7,2,10,8,15,78,34,23,66,44,23,5};
    selection_sort(numbers);
    for(auto& n : numbers)
    {
        std::cout << n << " ";
    }
    return 0;
}


