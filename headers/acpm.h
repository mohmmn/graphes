#ifndef ACPM_H_
#define ACPM_H_

#include "graph.h"

class ACPM : public Graph {
    public:
    ACPM(int n);
    void addEdge(int u, int v, int dist) override;
    int getNumberOfEdges() const override;
    void addNode(int n);
};
#endif // NONORIENTEDGRAPH_H_

