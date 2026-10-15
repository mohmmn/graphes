#include "../headers/ACPM.h";
#include "../headers/graph.h";
ACPM::ACPM (int n) : Graph(0){}

void ACPM::addEdge(int u, int v, int dist){
    this->adjacencyList[u].push_back({u,v,dist})
};

    int ACPM::getNumberOfEdges() const {
        int size = 0;
        for (int i = 0; i < this->adjacencyList.size(); i++){
            size += this->adjacencyList[i].size();
        }
        return size;
    };
    void ACPM::addNode(int n){
        this->adjacencyList.push_back(u);
    };