#include <iostream>
#include <array>

/*
    ---------------
    | pseudo code |
    ---------------

    bubble_sort(array arr) :
        for i:= 1 to arr.length-1 :
            for j:= arr.length downto i+1 :
                if arr[j] < arr[j-1] :
                    exchange arr[j] with arr[j-1]

    Note:
        pseudo code is implemented on 1 base indexing where below c++ code is implemented on 0 base indexing                
*/

template <size_t SIZE>
void bubble_sort(std::array<int,SIZE>& arr)
{
    for(int i = 0 ; i < arr.size()-1 ; i++)
    {
        for(int j = arr.size()-1 ; j >= i+1 ; j--)
        {
            if(arr[j]<arr[j-1])
                std::swap(arr[j],arr[j-1]);
        }
    }   

}

int main()
{
    std::array<int,10> arr{534,324,53,123,43,431,123,45,34,24};
    bubble_sort(arr);
    for(auto& val : arr)
    {
        std::cout << val << ' ';
    }
    return 0;
}