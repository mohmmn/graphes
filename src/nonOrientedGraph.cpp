#include "../headers/nonOrientedGraph.h"

NonOrientedGraph::NonOrientedGraph (int n) : Graph(n){}

void NonOrientedGraph::addEdge(int u, int v, int dist){
    this->adjacencyList[u].push_back({v,dist});
    this->adjacencyList[v].push_back({u,dist});
}
int NonOrientedGraph::getNumberOfEdges() const{
    int numberOfEdges = 0;
    for (const std::vector<Edge>& neighbours : this->adjacencyList) {
        numberOfEdges += static_cast<int>(neighbours.size());
    }
    return numberOfEdges/2;
}