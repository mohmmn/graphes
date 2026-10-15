#include "../headers/orientedGraph.h"

OrientedGraph::OrientedGraph (int n) : Graph(n){}

void OrientedGraph::addEdge(int u, int v, int dist){
    this->adjacencyList[u].push_back({v,dist});
}

int OrientedGraph::getNumberOfEdges() const {
    int numberOfEdges = 0;
    for (const std::vector<Edge>& neighbours : this->adjacencyList) {
        numberOfEdges += static_cast<int>(neighbours.size());
    }
    return numberOfEdges;
}