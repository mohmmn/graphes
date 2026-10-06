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

const std::vector<int>& Graph::getNeighbours(int node) const {
    return this->adjacencyList[node];
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
    for (int i : getNeighbours(node)) {
        if (!visited[i]) {
            dfsRec(i, visited, path);
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
        for (int i : getNeighbours(u)) {
            if (!visited[i]) {
                visited[i] = true;
                aVisiter.push(i);
            }
        }
    }
    return path;
}
