#include <iostream>
#include <vector>
#include <queue>

/*
    - Single source shortest path algo
    - Uses gready method
    - Does not work with negative weighted graph

    How does this work:
    Always selects the vertex with the shortest path then it update the shortest 
    path to other vertices if possible. This updation is called relaxation

    Relaxation :
    dis[v] = min(dis[v],dis[u]+ cost(u,v));

    Time complexity :
    0(|v|*|v|) = 0(n*n)
    with fibonacci heap 0(V+ElogV)
*/
#define total_vertices  6 
#define total_edges  8
int visited[total_vertices] = {0};
int distance[total_vertices] = {INT16_MAX};

void dijkstra(std::vector<std::vector<int>>& graph)
{  
    std::priority_queue<std::pair<int,int>,std::vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> pq;
    visited[0] = 1;
    distance[0] = 0;
    pq.push({0,0});
    while(!pq.empty())
    {
        std::pair<int,int> top_elem = pq.top();
        pq.pop();
        if(visited[top_elem.first])
            continue;
        visited[top_elem.first] = 1;
        for(int i = 0 ; i < total_vertices ; i++)
        {
            if(graph[top_elem.second][i]!= -1 && distance[top_elem.first] + graph[top_elem][i] < distance[top_elem.first][i])
            {
                distance[top_elem]
            }
        }
    }
}

int main()
{
    std::vector<std::vector<int>> graph = {
        {-1 , 2 , 4 , -1 , -1 , -1},
        {-1 , -1 , 1 , 7 , -1 , -1},
        {-1, -1 , -1 , -1, 3 , -1},
        {-1 , -1 , -1 , -1 , -1 , 1},
        {-1 , -1 , -1 , 2 , -1 , 5},
        {-1 , -1 , -1 , -1 , -1 , -1}
    };
    dijkstra(graph);
}