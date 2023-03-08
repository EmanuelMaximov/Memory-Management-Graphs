#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Tree.h"
#include "Session.h"

class Agent{
public:
    Agent()=default;//without the "=default" the CLion put a warning
    
    virtual void act(Session& session)=0;
    virtual void add(Session& session) const =0;
    virtual bool check(Session& session) = 0;
    virtual ~Agent()=default;
    virtual Agent* clone() const = 0;
};

class ContactTracer: public Agent{
public:
    ContactTracer()=default;//without the "=default" the CLion put a warning
    
    virtual void act(Session& session);
    virtual void add(Session& session) const;
    virtual bool check(Session& session);
    virtual ContactTracer* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd);
    
    virtual void act(Session& session);
    virtual void add(Session& session) const;
    virtual bool check(Session& session);
    virtual Virus* clone() const;
private:
    const int nodeInd;
};

#endif
