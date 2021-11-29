#include <iostream>
#include <vector>
#include <algorithm>

/*
    ---------------
    | pseudo code |
    ---------------

    find_max_crossing_sub_array(array arr , left , middle , right) :
        left_sum:= -inf
        total_sum:= 0

        for i:=middle downto left :
            total_sum = total_sum+arr[i]
            if total_sum > left_sum :
                left_sum = total_sum
        
        right_sum:= -inf
        total_sum:= 0

        for i:=middle+1 to right :
            total_sum = total_sum+arr[i]
            if total_sum > right_sum :
                right_sum = total_sum
        
        return max(left_sum,right_sum,left_sum+right_sum)
    
    find_maximum_sub_array(array arr, left , right) :
        if left == right :
            return arr[left]
        middle:= left+ (right-left)/2
        return max(find_maximum_sub_array(arr,left,middle),
                    find_maximum_sub_array(arr,middle+1,right),
                    find_max_crossing_sub_array(arr,left,middle,right))

*/

int find_max_crossing_sub_array(std::vector<int>& arr, int left , int mid , int right)
{
    int left_sum = INT_MIN ,
        total_sum = 0;
    for(int i = mid ; i >= left ; i--)
    {
        total_sum+= arr[i];
        if(total_sum > left_sum)
        {
            left_sum = total_sum;
        }
    }
    int right_sum = INT_MIN;
    total_sum = 0;
    for(int i = mid+1 ; i <= right ; i++)
    {
        total_sum+= arr[i];
        if(total_sum > right_sum)
        {
            right_sum = total_sum;
        }
    }
    return std::max(std::max(left_sum,right_sum), left_sum + right_sum);
}

int find_maximum_sub_array(std::vector<int>& arr , int left , int right)
{
    if(left==right)
        return arr[left];
    int mid = (left+right)/2 ;
    return std::max(std::max(find_maximum_sub_array(arr,left,mid),
                    find_maximum_sub_array(arr,mid+1,right)),
                    find_max_crossing_sub_array(arr, left, mid, right));
}

int main()
{
    std::vector<int> arr{2, -3, 4, -5, 7 };
    int max_sum = find_maximum_sub_array(arr,0,arr.size()-1);
    std::cout << "Maximum Subarray Sum is : " << max_sum ;
    return 0;
}
