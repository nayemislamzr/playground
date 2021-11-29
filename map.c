#include <stdio.h>
#include <stdint.h>

int sum (int a , int b)
{
    return a+b;
}

struct arithmatic
{
    int (*sum) (int a,int b);
};


int main()
{
    struct arithmatic a;
    a.sum = sum;
    printf("%d",a.sum(12,12));
}
