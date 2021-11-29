#include <iostream>
#include <list>
#include <vector>
#include <queue>

using namespace std;
/***
 * 0-indexed dijkstra implementation
 **/
class Graph 
{
    int vertices;
    list<pair<int,int>> *adjacencyList;
public :
    Graph() = delete;
    Graph(int _vertices);
    void addEdge(int vertex1, int vertex2, int weight);
    vector<int> getShortestPath(int src);
};

Graph::Graph(int _vertices)
    : vertices{_vertices} {
    adjacencyList = new list<pair<int,int>> [_vertices];
}

void Graph::addEdge(int vertex1, int vertex2, int weight)
{
    adjacencyList[vertex1].push_back({vertex2,weight});
    adjacencyList[vertex2].push_back({vertex1,weight});
}

vector<int> Graph::getShortestPath(int src)
{
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> walk;
    vector<int> distance(vertices,(int)10e6);
    walk.push({0,src});
    distance[0] = 0;
    while(!walk.empty())
    {
        pair<int,int> topComponent = walk.top();
        int topVertex = topComponent.second, topWeight = topComponent.first;
        walk.pop();
        for(auto neighbour : adjacencyList[topVertex])
        {
            int currVertex = neighbour.first, currWeight = neighbour.second; 
            if(distance[currVertex] > distance[topVertex] + currWeight)
            {
                distance[currVertex] = distance[topVertex] + currWeight;
                walk.push({distance[currVertex],currVertex});
            }
        }
    }
    return distance;
}

int main()
{
    vector<int> a = {12,123,12,3,123};
    queue<int> b(a.begin(),a.end());
}