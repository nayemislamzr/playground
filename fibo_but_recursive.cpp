#include <iostream>

int fibo(int i)
{
    if ( i == 1)
        return 1;
    else return i*fibo(i-1);    
}

int main()
{
    int n;
    scanf("%d",&n);
    printf("%d",fibo(n));
}