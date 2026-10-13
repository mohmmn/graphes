//
// Created by simo on 02/10/2026.
//
#include "../headers/graph.h"

#include <queue>

Graph::Graph(int n) {
    this->numberOfNodes = n;
    this->adjacencyList.resize(n);
}

Graph::~Graph() = default;

int Graph::getNumberOfNodes() const {
    return this->numberOfNodes;
}

const std::vector<Edge>& Graph::getNeighbours(int node) const {
    return this->adjacencyList[node];
}

int Graph::getDistEdge(int u, int v) const {
    for (const Edge& e : this->adjacencyList[u]) {
        if (e.to == v) {
            return e.dist;
        }
    }
    return -1;
}

std::vector<int> Graph::DFS(int node) const {
    std::vector<int> path;
    std::vector<bool> visited(this->numberOfNodes, false);
    dfsRec(node, visited,path);
    return path;
}

void Graph::dfsRec(int node, std::vector<bool> &visited, std::vector<int> &path) const{
    visited[node] = true;
    path.push_back(node);
    for (const Edge& e : getNeighbours(node)) {
        if (!visited[e.to]) {
            dfsRec(e.to, visited, path);
        }
    }
}

std::vector<int> Graph::BFS(int node) const {
    std::vector<int> path;
    std::vector<bool> visited(this->numberOfNodes, false);
    std::queue<int> aVisiter;
    visited[node] = true;
    aVisiter.push(node);
    while (aVisiter.empty() == false) {
        int u = aVisiter.front();
        aVisiter.pop();
        path.push_back(u);
        for (Edge e : getNeighbours(u)) {
            if (!visited[e.to]) {
                visited[e.to] = true;
                aVisiter.push(e.to);
            }
        }
    }
    return path;
}
