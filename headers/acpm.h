#ifndef ACPM_H_
#define ACPM_H_

#include "graph.h"
#include "nonOrientedGraph.h"

class ACPM : public NonOrientedGraph {
    public:
    ACPM(int n);
    // algorithme pour les arbres couvrant de poids minimal
    ACPM Kruskal();
    ACPM Prim(int node);
};
#endif // ACPM_H_

