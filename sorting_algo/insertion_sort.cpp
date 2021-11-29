#include <iostream>
#include <vector>

/*
    How this works:
    * Iterate from beginning to the end of the array . In each step compare the current 
      element with the previously sorted elements. and as long as the current element is smaller
      than any elements of the previously sorted elements make a space for the new one.

    Time complexity:
    * best case : 0(n) - when the array is already sorted
    * worst case : 0(n*n) - when the array is reversely sorted
    * average case : 0(n*n)

    space complexity:
    *0(1) no additional space needed.

    Works better when the array is almost sorted.
*/

void insertion_sort(std::vector<int>& numbers)
{
    for(int i = 0 ; i < numbers.size() ; i++)
    {
        int curr_element = numbers[i];
        int j = i - 1 ;
        while(j >= 0 && numbers[j] > curr_element)
        {
            numbers[j+1] = numbers[j];
            j--;
        }
        numbers[j+1] = curr_element;
    }
}

int main()
{
    std::vector<int> numbers = {5,7,2,10,8,15,78,34,23,66,44,23,5};
    insertion_sort(numbers);
    for(auto& n : numbers)
    {
        std::cout << n << " ";
    }
    return 0;
}