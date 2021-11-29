#include <iostream>
#include <vector>
/*
void merge ( std::vector<int>& arr , int start , int end , int mid )
{
       std::vector <int> temp (arr);
       int i,j,k;
       i=j=0;  k=start;
       int n = mid - start + 1 ; int m = end - mid ;
       while ( i < n && j < m)
       {
           if ( temp [start+i] < temp [mid + 1 + j])
                arr[k++] = temp[start+i++] ;
            else arr[k++] = temp[mid+1+j++] ;
       } 
       while( i < n)
            arr[k++] = temp[start+i++];
       while(j < m)
            arr[k++] = temp[mid+1+j++];
}

void merge_sort ( std::vector <int>& arr , int start , int end)
{
       if ( start >= end ) return ;

       int mid = (start+end)>>1;
       merge_sort (arr,start,mid);
       merge_sort (arr,mid+1,end);
       
       merge(arr,start,end,mid);
}
*/

int partition ( std::vector <int>& arr , int left , int right )
{
    bool r=true ;
    while ( left < right )
    {
        if ( arr[left] > arr [right] )
        {
            r^=1;
            std::swap(arr[left],arr[right]);
        }
        
        if(r)
            right--;
        else left++ ;    
    }
    return left ;
}

void quick_sort ( std::vector <int>& arr , int left , int right )
{
    if ( left >= right ) return ;
    int p = partition ( arr, left , right ) ;

    quick_sort (arr,left,p-1);
    quick_sort (arr,p+1,right);
}

int main ()
{
    int n ;
    std::cin >> n;
    std::vector <int> arr(n);
    for ( int i = 0 ; i < n ; i++)
    {
        std::cin >> arr[i];
    }
    
    quick_sort(arr,0,n-1);

    std::cout << "sorted array : " << std::endl ;

    for(int val: arr)
    {
        std::cout << val << " " ;
    }

    std::cout << std::endl ;
}