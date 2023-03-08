//
// Created by spl211 on 05/11/2020.
//

#include "../include/Session.h"
#include "../include/json.hpp"
#include <fstream>
#include "../include/Agent.h"
#include <iostream>
using json = nlohmann::json;
using namespace std;


Session::Session(const std::string& path) : g(), treeType(TreeType(0)), agents(std::vector<Agent*>()), infected(std::vector<int>()), currCycle(0), isYellow() {
    //read from json
    ifstream i(path);
    json j;
    i >> j;

    //assigning value from json
    Graph ng=Graph(j["graph"]);
    g = ng;
    isYellow = std::vector<bool>(g.getEdges().size());
    string c(j["tree"]);
    if (c == "M") {
        treeType = TreeType(1);
    }
    if (c == "C")
        treeType = TreeType(0);
    if (c == "R")
        treeType = TreeType(2);
    for(auto vec : j["agents"]){
        if (vec[0] == "V") {
            agents.push_back(new Virus(vec[1]));
            isYellow[vec[1]] = true;
        }
        if (vec[0] == "C") {
            agents.push_back(new ContactTracer());
        }
    }
}

//copy constructor
Session::Session(const Session &cs) : g(cs.g) , treeType(cs.treeType), agents(std::vector<Agent*>()), infected(std::vector<int>()), currCycle(cs.currCycle), isYellow(cs.isYellow) {

    for (auto &t:cs.agents) {
        addAgent(*t->clone());
    }
    for (auto &t:cs.infected) {
        enqueueInfected(t);
    }
}


//move constructor
Session::Session(Session &&cs) noexcept: g(cs.g) , treeType(cs.treeType), agents(std::move(cs.agents)), infected(cs.infected), currCycle(cs.currCycle) , isYellow(cs.isYellow) {
    cs.agents.clear();
}


//copy assignment operator
Session &Session::operator=(const Session &cs) noexcept{
    for (Agent* a : agents) {
        delete a;
    }
    agents.clear();
    for (size_t i = 0; i < cs.agents.size(); i++) {
        agents[i] = cs.agents[i]->clone();
    }
    infected = cs.infected;
    return *this;
}

//move assignment operator
Session &Session::operator=(Session &&cs) noexcept{
    if (&cs != this) {
        for(Agent* a: agents) {
            delete a;
        }
        agents.clear();
        for (Agent* a : agents) {
            agents.push_back(a);
            a = nullptr;
        }
        infected = cs.infected;
        currCycle = cs.currCycle;
        isYellow = cs.isYellow;
    }
    return *this;
}
Session::~Session() {
    for (auto &a:agents) {
        delete a;
    }
}

//the function that runs the program
void Session::simulate() {
    bool end = false;
    //main loop
    while (!end) {
        int size = agents.size();
        for(int i = 0; i < size; i++) {
            agents[i]->act(*this);
        }
        currCycle++;
        end = checkEnd();
    }

    //write to json
    json j;
    j["graph"] = getGraph().getEdges();
    j["infected"] = g.getInfected();
    std::ofstream o("output.json");
    o << j << endl;
}

bool Session::checkEnd() {
    for(auto & agent : agents) {
        if (!agent->check(*this)) {
            return false;
        }
    }
    return true;
}

//adds an agent to the agent queue
void Session::addAgent(const Agent &agent) {
    agent.add(*this);
}


//adds an infected node to the infected queue
void Session::enqueueInfected(int infect) {
    if (!g.isInfected(infect)){
        infected.push_back(infect);
        g.infectNode(infect);
    }
}

//dequeues an infected node from the infected queue and return its value
int Session::dequeueInfected() {
    int i = infected[0];
    infected.erase(infected.begin());
    return i;
}


TreeType Session::getTreeType() const {
    return treeType;
}

//visitor design pattern
void Session::addSAgent(const Virus &agent) {
    agents.push_back(new Virus(agent));

}
//visitor design pattern
void Session::addSAgent(const ContactTracer &agent) {
    agents.push_back(new ContactTracer(agent));
}

Graph Session::getGraph() const {
    return g;
}


bool Session::isInfected(int node) {
    return g.isInfected(node);
}

std::vector<int> Session::getInfected() const {
    return infected;
}

void Session::setEdges(std::vector<std::vector<int>> se) {
    g.setEdges(std::move(se));
}

int Session::getCycle() const{
    return currCycle;
}

bool Session::getYellow(int nodeInd) {
    return isYellow[nodeInd];
}

void Session::setYellow(int i, bool val) {
    isYellow[i] = val;
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}





