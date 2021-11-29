#include <vector>
#include <iostream>

/*
    - Single source shortest path algorithm.
    - Works on graph with negative cost.
    - uses dynamic programming

    How does this work:
    (i) First initialize all the edge distance except source to inf and set
    root to 0;
    (ii) relax all the edges |v| - 1 times as in a connected graph two vertices 
    at most can have |v| - 1 edges alongside it's way. 

    Relaxing logic :
    if the distance from root to vertice U & V is dis[U] , dis[V] ;
    then dis[V] = min (dis[v] , dis[u] + cost of (u,v))
 
    Time complexity :
    0(|E| * (|V| - 1)) where E = no of edges , V = no of vertices
    = 0(n*n)

    Auxiliary space :
    0(|V|) - to store the current distance from source to the vertices.

    Caution :
    Negative cycle can ruin your life . JK!
    we can not get shortest path on a graph having negative cycle. As the
    edges can be relaxed infinite number of times . so after |V| - 1 times
    relaxing there will be no relaxing if the graph has no negative cycle.
    So if at |v| time of relaxing we see relaxation of edge then definitely 
    the graph has a negative cycle.

*/

struct edge
{
    int from,to,weigh;
    edge(int mFrom , int mTo , int mWeight)
        : from{mFrom} , to{mTo} , weigh{mWeight}
    {

    }
};

int main()
{
    using std::vector;
    using std::iostream;

    std::vector<edge> edges{{0,1,6},{0,2,5},{0,3,5},{1,4,-1},{2,1,-2},{2,4,1},{3,2,-2},{3,5,-1},{4,6,3},{5,6,3}};
    vector<int> Distance = { 0 , INT8_MAX, INT8_MAX, INT8_MAX, INT8_MAX,INT8_MAX ,INT8_MAX};

    int total_vertices = 7;
    int total_edges = 10;

    for(int i = 0 ; i < total_vertices - 1 ; i++)
    {
        for(int j = 0 ; j < total_edges ; j++)
        {
            Distance[edges[j].to] = std::min (Distance[edges[j].to] , Distance[edges[j].from] + edges[j].weigh);
        }
    }

    for(int i = 0 ; i < total_vertices ; i++)
    {
        std::cout << "Node : " << i+1 << " , Dis : " << Distance[i] << '\n';
    }
}
