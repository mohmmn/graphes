#ifndef ORIENTEDGRAPH_H_
#define ORIENTEDGRAPH_H_
#include "graph.h"

class OrientedGraph : public Graph {
public:
    OrientedGraph(int n);
    void addEdge(int u, int v, int dist) override;
    int getNumberOfEdges() const override;
};
#endif // ORIENTEDGRAPH_H_