#include "../headers/nonOrientedGraph.h"

NonOrientedGraph::NonOrientedGraph (int n) : Graph(n){}

void NonOrientedGraph::addEdge(int u, int v){
    this->adjacencyList[u].push_back(v);
    this->adjacencyList[v].push_back(u);
}

int NonOrientedGraph::getNumberOfEdges() const{
    int numberOfEdges = 0;
    for (const std::vector<int>& neighbours : this->adjacencyList) {
        numberOfEdges += static_cast<int>(neighbours.size());
    }
    return numberOfEdges/2;
}