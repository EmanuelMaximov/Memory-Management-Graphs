//
// Created by spl211 on 05/11/2020.
//

#include "../include/Graph.h"

//constructor
Graph::Graph(std::vector<std::vector<int>> matrix) : edges(std::move(matrix)),
    infected(edges.size(),false){
}

Graph::Graph() :  edges(),infected() {}


void Graph::infectNode(int nodeInd) {
    infected[nodeInd]=true;
}

bool Graph::isInfected(int nodeInd) {
    return infected[nodeInd];
}

std::vector<std::vector<int>> Graph::getEdges() const {
    return edges;
}

std::vector<int> Graph::getInfected() {
    std::vector<int> inf;
    for (size_t i=0; i < infected.size(); i++) {
        if (infected[i]) {
            inf.push_back(i);
        }
    }
    return inf;
}

void Graph::setEdges(std::vector<std::vector<int>> se) {
    edges = std::move(se);
}


