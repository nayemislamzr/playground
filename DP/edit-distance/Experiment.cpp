#include <iostream>
using namespace std;


int main()
{
    int s,t,x;
    bool result = false;
    cin >> s >> t >> x;
    if(s>t) {
        if(x == 0)
            result = true;
        else if(x >= s && x <= 23)
            result = true;
        else if(x >= 0 && x <= t)
            result = true;
    }
    else {
        if(x >= s && x <= t)
            result = true;
    }
    if(result)
        cout << "Yes";
    else
        cout << "NO";
}