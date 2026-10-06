#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph {
protected:
    std::vector<std::vector<int>> adjacencyList;
    int numberOfNodes;
    // methode utilitaire DFS qui utilise la récursivité
    void dfsRec(int node, std::vector<bool> &visited, std::vector<int> &path) const;

public:
    // constructeur & destructeur
    Graph(int n);
    virtual ~Graph();
    // getters
    int getNumberOfNodes() const;
    virtual int getNumberOfEdges() const = 0;
    const std::vector<int>& getNeighbours(int node) const;
    // methodes abstraites
    virtual void addEdge(int u, int v) = 0;
    // algorithmes de parcours
    std::vector<int> DFS(int node) const;
    std::vector<int> BFS(int node) const;
};
#endif // GRAPH_H_