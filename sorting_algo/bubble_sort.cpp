#include <iostream>
#include <vector>

/*
    How this works :
    *Reapeatedly swapping the adjacent elments if they are in wrong order.
    *In each itertaion we get the most / min valuable number out of the array

    Time complexity:
    *Best Case : 0(n) - when the array is already sorted
    *Wrong Case : 0(n*n) - when the array is reversly sorted
    *Average Case : 0(n*n)

    Auxiliary Space : 0(1)
    Sorted in place : True
*/

void bubble_sort(std::vector<int>& numbers)
{
    for(int i = 0 ; i < numbers.size() - 1 ; i++) 
    {
        for(int j = 0 ; j < numbers.size() - i - 1 ; j++)
        {
            if( numbers[j] > numbers[j+1]) // checks if the adjacent elements in wrong order
                std::swap(numbers[j],numbers[j+1]); // swapping if the condition is true
        }
    }
}

int main()
{
    std::vector<int> numbers = {5,7,2,10,8,15,78,34,23,66,44,23,5};
    bubble_sort(numbers);
    for(auto& n : numbers)
    {
        std::cout << n << " ";
    }
    return 0;
}
