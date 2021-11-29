#include <iostream>
#include <vector>

/*
    How this works:
    * Divide and conquer algorithm
    Divides the input array into two halves. Then each halves also divides into two halves
    until there is only one half with only one element left.
    Then the algo merges the two halves until the array with the input array length .

    Time complexity:
    best case : 0(nlogn)
    worst case : 0(nlogn)
    average case : 0(nlogn)
    as each dividence and merging takes linear time . so it really not depends on the input array order.

    Auxiliary space : 0(n) 
*/

void merge(std::vector<int>& number , int start, int mid, int end)
{
    std::vector<int> temp(number);
    const int first_subarray_size = mid - start + 1,
    second_subarray_size = end - mid;
    int i = 0 , j = 0 , k = start ;
    while(i < first_subarray_size && j < second_subarray_size)
    {
        if(temp[i+start] < temp[j+mid+1])
        {
            number[k] = temp[i+start];
            i++;
        }
        else 
        {
            number[k] = temp[j+mid+1];
            j++;
        }
        k++;
    }
    while(i < first_subarray_size)
    {
        number[k] = temp[i+start];
        i++;
        k++;
    }
    while (j < second_subarray_size)
    {
        number[k] = temp[j+mid+1];
        j++;
        k++;
    }
    
}

void merge_sort(std::vector<int>& number , int start, int end)
{
    if(start >= end)
        return;
    int mid = (start+end)/2;
    merge_sort(number,start,mid);
    merge_sort(number,mid+1,end);
    merge(number,start,mid,end);
}

int main()
{
    std::vector<int> numbers = {5,7,2,10,8,15,78,34,23,66,44,23,5};
    merge_sort(numbers,0,numbers.size()-1);
    for(auto& n : numbers)
    {
        std::cout << n << " ";
    }
    return 0;
}
