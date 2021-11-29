#include <iostream>
#include <vector>

bool binary(int i , int j , std::vector<int> arr, int x)
{
    int m = (i+j)/2 ;
    if (arr[m] == x)
        return true;
    else if (arr[m]>x)
        return (i,m-1,arr,x);
    else if (arr[m]<x)
        return (m+1,j,arr,x);       
    else return false;    
}

int main()
{
    std::vector<int> arr = {12,23,42,67,877,97868,657567};
    printf("%d",binary(0,arr.size(),arr,24));
}