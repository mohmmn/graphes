#include "../headers/orientedGraph.h"
#include "../headers/nonOrientedGraph.h"

#include <iostream>
#include <vector>

// affiche une liste de sommets separes par des espaces
void printList(const std::vector<int> &list) {
    for (int node : list) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

// affiche la liste d'adjacence, le nombre de sommets / aretes et les parcours DFS / BFS
void printGraph(const Graph &graph, int start) {
    std::cout << "Liste d'adjacence :" << std::endl;
    for (int node = 0; node < graph.getNumberOfNodes(); node++) {
        std::cout << "  " << node << " -> ";
        printList(graph.getNeighbours(node));
    }

    std::cout << "Nombre de sommets : " << graph.getNumberOfNodes() << std::endl;
    std::cout << "Nombre d'aretes   : " << graph.getNumberOfEdges() << std::endl;
    std::cout << "DFS depuis " << start << "      : ";
    printList(graph.DFS(start));
    std::cout << "BFS depuis " << start << "      : ";
    printList(graph.BFS(start));
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Voici un graphe non oriente de 5 sommets ===" << std::endl;
    NonOrientedGraph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    printGraph(g, 0);

    std::cout << "=== Voici un graphe oriente de 5 sommets ===" << std::endl;
    OrientedGraph d(5);
    d.addEdge(0, 1);
    d.addEdge(0, 2);
    d.addEdge(1, 3);
    d.addEdge(3, 4);
    d.addEdge(4, 1);
    printGraph(d, 0);

    return 0;
}
