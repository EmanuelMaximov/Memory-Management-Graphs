//
// Created by spl211 on 05/11/2020.
//

#include "../include/Agent.h"

Virus::Virus(int nodeInd) : nodeInd(nodeInd){
}

void Virus::act(Session& session) {
    session.enqueueInfected(nodeInd);
    session.setYellow(nodeInd, false);

    //finds the leftmost neighbor node thats not infected yet and add a virus with that nodes value
    for (size_t i = 0; i < session.getGraph().getEdges().size(); i++) {
        if (session.getGraph().getEdges()[nodeInd][i] == 1 && !session.isInfected(i) && !session.getYellow(i)) {
            session.addSAgent(Virus(i));
            session.setYellow(i, true);
            return;
        }
    }

}
void Virus::add(Session &session) const {
    session.addSAgent(*this);
}


//check if a virus is done infecting all its neigboring nodes - true if it is done
bool Virus::check(Session& session) {
    bool ans = !session.getYellow(nodeInd);
    for (size_t i = 0; i < session.getGraph().getEdges().size() && ans; i++) {
        if (session.getGraph().getEdges()[nodeInd][i] == 1) {
            ans = session.isInfected(nodeInd) == session.isInfected(i);
        }
    }
    return ans;
}

Virus *Virus::clone() const {
    return new Virus(*this);
}
