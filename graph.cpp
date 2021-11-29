#include <iostream>
#include <vector>
#include <queue>
#include <cstdbool>

class AdjMatrix{
private:
    int* AdjG ;
    int nodes ,  edges ;
public:
    AdjMatrix(int __nodes , int __edges){
        nodes = __nodes ;
        edges = __edges ;
        AdjG = new int[nodes * nodes] ;
        std::fill(AdjG , AdjG+nodes*nodes , 0);
    }

    void add(){
      int node_a ,  node_b ;  
      for(int i = 0 ; i < edges ; i++ ){
        std::cin >> node_a >> node_b ;
        *((AdjG+node_a*nodes) + node_b) = 1 ;
      }
    }

    void print(){
        for (int curr_node = 0 ; curr_node < nodes ; curr_node++){
            std:: cout << curr_node << " : " ;
            for (int curr_edge = 0 ; curr_edge < nodes ; curr_edge++){
                std::cout << " | " << *((AdjG+curr_node*nodes)+ curr_edge) << " | " ;
            }
            std::cout << std::endl;
        }
    }    
};

class AdjListGraph{
private:
    std::vector<int> *g ;
    int nodes ,  edges ;    
public:
   AdjListGraph(int __nodes, int __edges){
        nodes = __nodes ;
        edges = __edges ;
        g = new std::vector<int> [nodes];
    }

    void add() {
        int node_a , node_b ;
        for (int i = 0 ; i < edges ; i++){
            std::cin >> node_a >> node_b ;
            g[node_a].push_back(node_b);
        }
    }

    void print(){
       for (int curr_node = 0 ; curr_node < nodes ; curr_node++ ){
           std:: cout << curr_node << " : " ;
           for( int  edge : g[curr_node]){
               std:: cout << " | " <<  edge << " |  " ;
           }
           std::cout << std::endl ;
       } 
    }

    void DFSutil(int curr_node , bool visited[]){
        visited[curr_node] = true ;
        for (int connected_node : g[curr_node]){
            if(!visited[connected_node]){
                std::cout << connected_node << " ";
                DFSutil(connected_node, visited);
            }
        }
    }
    void DFS(int v){        //uses stack to implement ;
        bool* visited = new bool[nodes]; 
        std::fill(visited,visited+nodes,false);  
        DFSutil(v , visited);
    }

    void BFS(int v){  //uses queue to implement
        bool* visited = new bool[nodes];
        std::fill(visited,visited+nodes,false);
        visited[v] = true ;
        std::queue <int> QGraph ;
        QGraph.push(v);
        while(!QGraph.empty()){
            int top = QGraph.front();
            QGraph.pop();
            for (int node : g[top]){
                if(!visited[node]){
                    std::cout << node << " ";
                    visited[node] = true ;
                    QGraph.push(node);
                }
            }
        }
        std::cout << std::endl ;
    }

    // *** Spanning Tree ***
    
    // lets say 'G'  is a graph of 'V' vertex and 'E' edges [G(V,E)]
    // All the vertex(nodes) must be connected
    // So , the spanning tree is a sub set of G [ S is a subset of G ] , where S(V`,E`) , here V` = V but E = V - 1
    // Minimum Spanning Tree algorithms (MST) :
    //  1. Kruskal's Algorithm
    //  2. Prim's Algorithm
    //
    // now , lets say we have graph of 'V' vertex and 'E' edges . now the question is how many spanning tree is possible out of it ?
    
    // Answer :
    // E
    //   C        -  no . of cycle(s)
    //     V-1

    
};

int main() {
    int nodes , edges ;
    std::cin >> nodes >> edges ;
    AdjListGraph* my_graph = new AdjListGraph( nodes , edges);
    my_graph->add();
    // my_graph->print();
    my_graph->DFS(2) ;
    std::cout << std::endl ;
    my_graph->BFS(2);
    
    // AdjMatrix* my_graph = new AdjMatrix(nodes, edges);
    // my_graph->add();
    // my_graph->print();
}