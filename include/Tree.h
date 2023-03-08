#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <queue>
#include "Graph.h"
#include "Session.h"

class Session;

class Tree{
public:
    Tree(int rootLabel);
    Tree(const Tree& ct);
    Tree(Tree&& ct);
    const Tree& operator=(const Tree& ct);
    const Tree& operator=(Tree&& ct);
    virtual ~Tree();

    void clear();
    virtual Tree* clone() const =0;
    void addChild(const Tree& child);
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;
    std::vector<Tree*> getChildren() const;
    int getNode() const;
    static Tree* createNode(TreeType tt, int nodeInd, int cycle);

private:
    int node;
    std::vector<Tree*> children;
    static void bfs(Tree* tree, const Graph& g, TreeType tt);

};

class CycleTree: public Tree{
public:
    virtual Tree* clone() const;
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    virtual Tree* clone() const;
    MaxRankTree(int rootLabel);
    virtual int traceTree();

};

class RootTree: public Tree{
public:
    virtual Tree* clone() const;
    RootTree(int rootLabel);
    virtual int traceTree();
};

#endif
