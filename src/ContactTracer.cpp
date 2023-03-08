//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"

void ContactTracer::act(Session &session) {
    if(!session.getInfected().empty()) {
        int root = session.dequeueInfected();
        Tree *tree = Tree::createTree(session, root); //builds a tree based on the 'root'
        int remove = tree->traceTree(); // remove <- the node to remove from the tree based on tree type
        //build a new and updated graph after we remove a node's edges
        int len = session.getGraph().getEdges().size();
        std::vector<std::vector<int>> newEdges;
        newEdges = session.getGraph().getEdges();
        //removes the edges of 'remove' node from the graph
        for (int i = 0; i < len; i++) {
            newEdges[remove][i] = 0;
            newEdges[i][remove] = 0;
        }
        session.setEdges(newEdges);
        delete tree;
    }
}

//visitor design pattern
void ContactTracer::add(Session &session) const {
    session.addSAgent(*this);
}

//checks if an agent is ready to end - allways true for contact tracer
bool ContactTracer::check(Session &session) {
    return true;
}

ContactTracer* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

