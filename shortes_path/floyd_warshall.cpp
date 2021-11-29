#include <iostream>
#include <vector>

/*
    - All pair shortest path
    
    How does this work :
    (i) uses dynamic programming . first make a distance matrix representing the the 
    distance between the vertices . if no direct edge found make them infinite. 
    
    (ii) then keep relaxing the distance in the matrix n times where n = no of vertices.

    relaxing logic :
    let u , v vertices have a edge .
    now , d[v] = min (d[v] , d[u] + d[v]) 

    time complexity :
    O(n) - where n is the number of vertices.
*/

int main()
{
    using std::vector;

    /*
             2
        1 <-------> 2
        /\ /\   8   | 
        | 2   \     | 2
      7  |     5\   |
       \/        \ \/
        4 <------->3    
            1
    */

    vector<vector<int>> distance = {
                       {0,  3 , INT8_MAX , 7 },
                       {8 , 0 , 2 , INT8_MAX},
                       {5 , INT8_MAX , 0 , 1},
                       {2 , INT8_MAX , INT8_MAX , 0}
                    };

    for(int i = 0 ; i < 4 ; i++)
    {
        for(int u = 0 ; u < 4 ; u++)
        {
            for(int v = 0 ; v < 4 ; v++)
            {
                distance[u][v] = std::min(distance[u][v], distance[u][i] + distance[i][v]);
            }
        }
    }

    for(int u = 0 ; u < 4 ; u++)
    {
        for(int v = 0 ; v < 4 ; v++)
        {
            std::cout << distance[u][v] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}