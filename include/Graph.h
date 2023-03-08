#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    Graph(const Graph& cg)=default;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    std::vector<std::vector<int>> getEdges() const;
    std::vector<int> getInfected();
    void setEdges(std::vector<std::vector<int>> se);
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infected;
};

#endif
