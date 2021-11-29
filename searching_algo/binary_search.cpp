#include <iostream>
#include <vector>

/*
    Note :
    Only works with the sorted array (needs to be contious block of memory) 
    
    How this works :
    divides the array in two part(range). compares the element with two parts then .
    checks if the array in which range then again does the same process until finds the element.

    Time complexity:
    Best case : 0(1)
    Worst case : 0(logn)
    Average case : 0(logn)

    Auxiliary space : 0(1)
*/

bool binary_search(std::vector<int>& number ,int start , int end,  int search_element)
{
    if (start == end)
        return (search_element == number[start]);
    int mid = (start+end)/2;
    if(number[mid] == search_element)
        return true;
    else if(number[mid] > search_element)
        return binary_search(number,start,mid-1,search_element);
    else return binary_search(number,mid+1,end,search_element);
    return false;
}
int main()
{
    std::vector<int> numbers = {5,10,15,23,45,66,88,99};
    int search_element;
    std::cin >> search_element;
    if(binary_search(numbers,0,numbers.size()-1,search_element))
        std::cout << "Search found!!!" << std::endl;
    else 
        std::cout << "Not found!!!" << std::endl;
    return 0;
}