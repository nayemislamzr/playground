#include <iostream>
#include <vector>
#define MAX 100
std::vector<int> parent(MAX);

/*
    ---------------
    | pseudo code |
    ---------------

    makeset(n) :
        for i:=1 to n :
            parent[i] = i

    Find(representative) :
        if(parent[representative] == representative) :
            return representative
        return parent[representative] = Find(parent[representaive])

    Union(first,second) :
        if Find(first) == Find(second) :
            print they are already friend
        else
            parent[first] = second

    Friend(first,second) :
        return Find(first) == Find(second) 
*/


void makeset(int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        parent[i] = i;
    }
}

int Find(int representative)
{
    if(parent[representative] == representative)
    {
        return representative;
    }
    return parent[representative] = Find(parent[representative]);
}

void Union(int first, int second)
{
    int first_representative = Find(first);
    int second_representative = Find(second);
    if(first_representative==second_representative)
    {
        std::cout << "They are already friends" << std::endl;
    }
    else 
    {
        parent[first] = second;
    }
}

bool Friend(int first,int second)
{
    return Find(first)==Find(second);
}

int main()
{
    makeset(5);
    Union(1,2);
    Union(2,3);
    std::cout << Friend(1,3) << " " << Friend(1,4);
}
