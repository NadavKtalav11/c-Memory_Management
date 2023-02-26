#pragma once

#include <vector>

class SelectionPolicy;
class Simulation;

class Agent
{
public:
    Agent(int, int, SelectionPolicy*);
    Agent(Agent& ,int, int);

        // Destructor
    ~Agent();
    // Copy constructor
    Agent(const Agent&);
    // Move constructor
    Agent(Agent&&);
    // Copy assignment operator
    Agent& operator=(const Agent&);
    // Move assignment operator
    Agent& operator=(Agent&&);


    int getPartyId() const;
    int getId() const;
    void step(Simulation&);
    int getCoalitionId();

private:
    int mAgentId;
    int mPartyId;
    int coalitionId;
    SelectionPolicy *mSelectionPolicy;
};
