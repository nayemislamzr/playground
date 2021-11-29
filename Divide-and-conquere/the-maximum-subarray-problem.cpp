#include <iostream>
#include <vector>

using namespace std;



int main()
{
    int n ;
    cin >> n;
    vector<int> price(n), priceDifference(n,0);
    for(int i = 0 ; i < n ; i++)
        cin >> price[i];
    for(int i = 1 ; i < n ; i++)
        priceDifference[i] = price[i] - price[i-1];
}