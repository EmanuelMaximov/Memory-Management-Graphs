//
// Created by spl211 on 06/11/2020.
//

#include "../include/Tree.h"
#include <queue>

//constructor
Tree::Tree(int rootLabel) : node(rootLabel), children()  {

}

//destructor
Tree::~Tree() {
    clear();
}

void Tree::clear() {
    for(Tree* child:children) {
            delete (child);
    }
    children.clear();
}
//------------------------------------------------------------------------------
//copy constructor
Tree::Tree(const Tree& ct) : node(ct.node), children() {
      for (uint i=0;i<ct.children.size();i++)
          children.push_back(ct.children[i]->clone());
}

//move constructor
Tree::Tree(Tree&& ct)  : node(ct.node), children(std::vector<Tree*>(ct.children.size())) {
    children = ct.children;
    ct.children.clear();
}


//copy assignment operator
const Tree& Tree::operator=(const Tree& ct) {
    if (this != &ct) {
        node = ct.getNode();
        clear();
        for (Tree* child: ct.children)
        {
            children.push_back(child->clone());
        }

    }
    return *this;
}

//move assignment operator
const Tree& Tree::operator=(Tree&& ct) {
    if (this != &ct) {
        node = ct.getNode();
        for (Tree* child: children) {
            delete child;
        }
        children.clear();
        for (Tree* &child: ct.children) {
            children.push_back(child);
            child = nullptr;
        }

        for(Tree* child : ct.children) {
            delete child;
        }
        ct.children.clear();
    }
    return *this;
}
std::vector<Tree*> Tree::getChildren() const {
    return children;
}

int Tree::getNode() const {
    return node;
}


void Tree::addChild(const Tree &child) {
    children.push_back(child.clone()); //using const cast because we are not altering the tree 'child'
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree* tree = createNode(session.getTreeType(), rootLabel, session.getCycle());
    bfs(tree, session.getGraph(), session.getTreeType());
    return tree;
}

void Tree::bfs(Tree *tree, const Graph& g, TreeType tt) {
    {
        // Mark all the vertices as not visited
        std::vector<bool> visited(g.getEdges().size());
        for(size_t i = 0; i < g.getEdges().size(); i++)
            visited.at(i) = false;

        // Create a queue for BFS
        std::vector<Tree*> queue;
        // Mark the current node as visited and enqueue it
        visited[tree->getNode()] = true;
        queue.push_back(tree);

        while(!queue.empty())
        {
            // Dequeue a vertex from queue
            Tree* s = queue.front();
            queue.erase(queue.begin());

            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it

            for(size_t i = 0; i < g.getEdges().size(); i++) {
                if(g.getEdges().at(s->getNode()).at(i) == 1 && !visited.at(i)) {
                    Tree* newTree = createNode(tt, i,0);
                    visited.at(i) = true;
                    s->addChild(*newTree);
                    delete(newTree);
                }
            }
            for(auto child : s->children) {
                queue.push_back(child);
            }

        }
    }
}

Tree *Tree::createNode(TreeType tt, int nodeInd, int cycle) {
    Tree* newTree;
    switch (tt){
        case TreeType::Cycle:
            newTree = new CycleTree(nodeInd,cycle); break;
        case TreeType::MaxRank:
            newTree = new MaxRankTree(nodeInd); break;
        case TreeType::Root:
            newTree = new RootTree(nodeInd); break;
        default: return nullptr;
    }
    return newTree;
}



CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() {
        Tree* curr = this;
        for (int i = 0; i < currCycle && !(curr->getChildren().empty()); i++) {
            curr = curr->getChildren().at(0);
        }
    return curr->getNode();
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {

}


int MaxRankTree::traceTree() {
    std::queue<Tree*> queue;
    uint max = 0;
    int res = getNode();
    Tree* curr;
    queue.push(this);

    //a bfs run on the Tree and searching for the first node with the max number of neighbors
    while(!queue.empty()) {
        curr = queue.front();
        queue.pop();
        for (size_t i = 0; i < curr->getChildren().size(); i++) {
            queue.push(curr->getChildren()[i]);
        }
        if (curr->getChildren().size() > max) {
            max = curr->getChildren().size();
            res = curr->getNode();
        }
    }
    return res;
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}


RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() {
    return getNode();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}

