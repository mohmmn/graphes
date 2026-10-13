#ifndef NONORIENTEDGRAPH_H_
#define NONORIENTEDGRAPH_H_

#include "graph.h"

class NonOrientedGraph : public Graph {
    public:
    NonOrientedGraph(int n);
    void addEdge(int u, int v,int dist) override;
    int getNumberOfEdges() const override;
};
#endif // NONORIENTEDGRAPH_H_

