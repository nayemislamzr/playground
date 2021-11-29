#include <iostream>

#define sz 1000

int partition(int arr[],int left ,int right)
{
    bool r = true;
    while(left < right)
    {
        if(arr[left] > arr[right])
           {
               std::swap(arr[left],arr[right]);
               r^=1;
           }
        if(r)
            right--;
        else 
            left++;   
    }
    return left;
}

void quicksort(int arr[], int l , int r)
{
    if ( l >= r) return;
    
    int p = partition (arr,l,r);
    quicksort(arr,l,p-1);
    quicksort(arr,p+1,r);
}

int main()
{
    int arr[sz];
    int n;
    std::cin >> n ;
    for ( int i = 0  ; i < n ; i++ )
    {
        std::cin >> arr[i];
    }
    
    quicksort(arr,0,n-1) ;
    std::cout << "Sorted Array : " << std::endl;
     
    for ( int i = 0 ; i < n ; i++ )
    {
        std::cout << arr[i] << " ";
    } 
    return 0;
}