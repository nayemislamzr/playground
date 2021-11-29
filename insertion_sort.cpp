#include <iostream>
#include <array>

/*
    ---------------
    | pseudo code |
    ---------------
    insertion_sort(array arr) :
        for i:=2 to i < arr.length :
            key:= arr[i]
            j:= i-1
            while j>0 and arr[j]>key :
                arr[j+1]=arr[j]
                j=j-1
            arr[j+1]=key

    Note:
        pseudo code is implemented on 1 base indexing where below c++ code is implemented on 0 base indexing 
*/
template<std::size_t SIZE>
void insertion_sort(std::array<int,SIZE>& arr)
{
    for(size_t i = 1 ; i < arr.size() ; i++)
    {
        int val = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>val)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = val;
    }
}

int main()
{
    std::array<int, 10> arr{534,324,53,123,43,431,123,45,34,24};
    insertion_sort(arr);
    for(auto& val : arr)
    {
        std::cout << val << ' ';
    }
    return 0;
}