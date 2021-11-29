#include <iostream>
#include <vector>

/*
    ---------------
    | pseudo code |
    ---------------

    merge(array arr , left , middle , right) :
        left_sub_array_size:=middle - left + 1
        right_sub_array_size:=right - middle

        let left_sub_array of size left_sub_array_size 
        and right_sub_array of size right_sub_array_size

        for i:=1 to left_sub_array_size :
            left_sub_array[i] = arr[left+i]

        for i:=1 to right_sub_array_size :
            right_sub_array[i] = arr[middle+1+i]
        
        left_sub_array_index:=0
        right_sub_array_index:=0
        marged_array_index:=left

        while left_sub_array_index <= left_sub_array_size and right_sub_array_index <= right_sub_array_size :
            if left_sub_array[left_sub_array_index] <= right_sub_array[right_sub_array_index] :
                arr[marged_array_index] = left_sub_array[left_sub_array_index]
                left_sub_array_index = left_sub_array + 1
            else :
                arr[marged_array_index] = right_sub_array[right_sub_array_index]
                right_sub_array_index = right_sub_array_index + 1
            marged_array_index = marged_array_index + 1
        
        while left_sub_array_index <= left_sub_array_size :
            arr[marged_array_index] = left_sub_array[left_sub_array_index]
            left_sub_array_index = left_sub_array + 1
            marged_array_index = marged_array_index + 1
        
        while right_sub_array_index <= right_sub_array_size :
            arr[marged_array_index] = right_sub_array[right_sub_array_index]
            right_sub_array_index = right_sub_array_index + 1
            marged_array_index = marged_array_index + 1

    merge_sort(array arr , start , end) :
        if start >= end
            return
        middle:= start + (end-start)/2
        merge_sort(arr,start,middle)
        merge_sort(arr,middle+1,end)
        merge(arr,start,middle,end)
    
    Note:
        pseudo code is implemented on 1 base indexing where below c++ code is implemented on 0 base indexing
*/

void merge(std::vector<int>& arr , const size_t begin , const size_t mid , const size_t end)
{
    size_t left_sub_array_size = mid-begin+1;
    size_t right_sub_array_size = end-mid;
    std::vector<int> left_sub_array(left_sub_array_size);
    std::vector<int> right_sub_array(right_sub_array_size);

    for(int i = 0 ; i < left_sub_array_size ; i++)
    {
        left_sub_array[i] = arr[begin+i];
    }
    
    for(int i = 0 ; i < right_sub_array_size ; i++)
    {
        right_sub_array[i] = arr[mid+1+i];
    }
    
    size_t left_sub_array_index {0},
            right_sub_array_index {0},
            merged_array_index {begin};
    while(left_sub_array_index < left_sub_array_size && right_sub_array_index < right_sub_array_size)
    {
        if(left_sub_array[left_sub_array_index] <= right_sub_array[right_sub_array_index])
        {
            arr[merged_array_index++] =  left_sub_array[left_sub_array_index++];
        }
        else
        {
            arr[merged_array_index++] = right_sub_array[right_sub_array_index++];
        }
    }
    while(left_sub_array_index < left_sub_array_size)
    {
        arr[merged_array_index++] = left_sub_array[left_sub_array_index++];
    }
    while(right_sub_array_index < right_sub_array_size)
    {
        arr[merged_array_index++] = right_sub_array[right_sub_array_index++];
    }
}

void merge_sort(std::vector<int>& arr , const size_t begin , const size_t end)
{
    if(begin>=end)
        return;
    size_t mid = begin + (end-begin)/2 ;
    merge_sort(arr,begin,mid); 
    merge_sort(arr,mid+1,end);
    merge(arr,begin,mid,end);
}

int main()
{
    std::vector<int> arr{23,34,32,4,5665,324,3435,2,14325,32};
    merge_sort(arr,0,arr.size()-1);
    for(auto& val : arr)
    {
        std::cout << val << ' ';
    }
    return 0;
}