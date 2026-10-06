#include "../headers/orientedGraph.h"

OrientedGraph::OrientedGraph (int n) : Graph(n){}

void OrientedGraph::addEdge(int u, int v){
    this->adjacencyList[u].push_back(v);
}

int OrientedGraph::getNumberOfEdges() const {
    int numberOfEdges = 0;
    for (const std::vector<int>& neighbours : this->adjacencyList) {
        numberOfEdges += static_cast<int>(neighbours.size());
    }
    return numberOfEdges;
}