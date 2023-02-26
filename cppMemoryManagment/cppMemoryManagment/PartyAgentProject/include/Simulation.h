#pragma once

#include <vector>
#include <string>

#include "Graph.h"
#include "Party.h"

using std::string;
using std::vector;

// class Agent;

class Simulation
{
public:
    // constructor
    Simulation(Graph, vector<Agent>);


    void step();
    bool shouldTerminate() const;
    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getParty(int partyId) ;
    Graph &getGraph();
    Agent& getAgent(int agentId);
    vector<Agent> &getAgents();
    const vector<vector<int>> getPartiesByCoalitions() const;
    void addPartyToCoalition(int coalitionId , int partyId);
    const int getTotalCoalitionMandates(int coalitionId) const;
    void clone(int , int );
    void addFirstCoalitions();
    
private:

    Graph mGraph;
    vector<Agent> mAgents;
    vector<vector<int>> coalitions;
    vector<int> mandatesByCoalition;
};