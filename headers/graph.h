#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

struct Edge {
    int to;
    int dist;
};

struct FullEdge {
    int from;
    int to;
    int dist;
};

class Graph {
protected:
    std::vector<std::vector<Edge>> adjacencyList;
    int numberOfNodes;
    // methode utilitaire DFS qui utilise la récursivité
    void dfsRec(int node, std::vector<bool> &visited, std::vector<int> &path) const;

public:
    // constructeur & destructeur
    Graph(int n);
    virtual ~Graph();

    // getters
    int getNumberOfNodes() const;
    const std::vector<Edge>& getNeighbours(int node) const;
    // renvoie -1 s'il n'y a pas d'arete entre u et v
    int getDistEdge(int u, int v) const;

    // methodes abstraites
    virtual void addEdge(int u, int v, int dist) = 0;
    virtual int getNumberOfEdges() const = 0;

    // algorithmes de parcours
    std::vector<int> DFS(int node) const;
    std::vector<int> BFS(int node) const;

    // algorithme de tri
    std::vector<FullEdge> sortFullEdges() const;
    // algorithme pour les arbres couvrant de poids minimal
    ACPM Kruskal();
    ACPM Prim(int node);
    
};
#endif // GRAPH_H_