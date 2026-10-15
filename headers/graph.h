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
std::vector<FullEdge> sortFullEdge(){
    for (int i = 1; i < fullEdgesSorted.size(); i++) {
        int j = i;
        while (j > 0 && fullEdgesSorted[j].dist < fullEdgesSorted[j-1].dist) {
            FullEdge tmp = fullEdgesSorted[j];
            fullEdgesSorted[j] = fullEdgesSorted[j-1];
            fullEdgesSorted[j-1] = tmp;
            j--;
        }
    }
}

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

    // algorithme pour les arbres couvrant de poids minimal
    Graph Kruskal();
    Graph Prim(int node);

    // algorithme de tri
    std::vector<FullEdge> sortFullEdges() const;
};
#endif // GRAPH_H_