#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

class Agent;
class Virus;
class ContactTracer;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{

public:
    Session(const std::string& path);

    Session(const Session& cs);
    Session(Session&& cs) noexcept;
    Session& operator=(const Session& cs) noexcept;
    Session& operator=(Session&& cs) noexcept;
    virtual ~Session();

    void simulate();
    void addAgent(const Agent& agent);

    bool checkEnd();
    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    void addSAgent(const Virus& agent);
    void addSAgent(const ContactTracer& agent);
    Graph getGraph() const ;
    void setGraph(const Graph& graph);
    bool isInfected(int node);
    std::vector<int> getInfected() const;
    void setEdges(std::vector<std::vector<int>> se);
    int getCycle() const;
    bool getYellow(int nodeInd);
    void setYellow(int i, bool val);
private:

    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::vector<int> infected;
    int currCycle;
    std::vector<bool> isYellow;
};

#endif
