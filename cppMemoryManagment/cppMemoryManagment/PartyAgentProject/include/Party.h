#pragma once

#include "Agent.h"
#include "Simulation.h"
#include "JoinPolicy.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// class JoinPolicy;
// class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    // Destructor
    ~Party();
    // Copy constructor
    Party(const Party&);
    // Move constructor
    Party(Party&&);
    // Copy assignment operator
    Party& operator=(const Party&);
    // Move assignment operator
    Party& operator=(Party&&);


    State getState() const;
    void setState(State state);
    int getId() const;
    int getMandates() const;
    void step(Simulation&);
    const string &getName() const;
    void selectCoalition();
    int getLastPartyToJoin();
    const int getCoalition() const;
    void collectOffer(Agent&) ;
    int getnumberOfOffers();
    Agent& getOfferByAgentsAt(int);
    int getOfferByAgentsSize();
    void setCoalitionId(int);
  

private:

    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int coalitionId;
    int coolDown;
    vector<Agent> offersByAgents;
};
