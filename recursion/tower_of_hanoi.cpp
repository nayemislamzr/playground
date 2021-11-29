#include <iostream>
using namespace std;

/*
    How this works:
    we are given 3 rods(A, B , C). we have to move n disk from one rod to another.
    But 
    (i) we can move only one disk at a time
    (ii) we can only move the top disk
    (iii) No disk may be placed on top of a smaller disk.

    Approach :
    Move n-1 disks from A to B using C.
    Move 1 disk from A to C .
    Move n-1 disks from B to C using A.

    Time complexity :

*/
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)
    {
        cout << "Move disk 1 from rod " << from_rod <<
                            " to rod " << to_rod<<endl;
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod <<
                                " to rod " << to_rod << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main()
{
    int n;
    std::cin >> n;
    towerOfHanoi(n,'A','C','B');
}