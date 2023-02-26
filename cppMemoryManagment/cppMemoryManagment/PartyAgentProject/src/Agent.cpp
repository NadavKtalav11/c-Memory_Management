#include "../include/Agent.h"
#include "../include/SelectionPolicy.h"
#include "../include/Party.h"
#include <iostream>

using std::cout;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), coalitionId(agentId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
    
}

Agent::Agent(Agent& agentToClone ,int agentId, int partyId) : mAgentId(agentId), mPartyId(partyId), coalitionId(agentToClone.coalitionId), mSelectionPolicy(agentToClone.mSelectionPolicy->copy())
{    
}
// copy constructor
Agent::Agent(const Agent& other):mAgentId(other.mAgentId), mPartyId(other.mPartyId),coalitionId(other.coalitionId) ,mSelectionPolicy(other.mSelectionPolicy->copy()) 
{}


// move constructor
Agent::Agent(Agent&& other):  mAgentId(other.mAgentId), mPartyId(other.mPartyId),coalitionId(other.coalitionId), mSelectionPolicy(other.mSelectionPolicy)
 {
    other.mSelectionPolicy = nullptr;
}




Agent::~Agent()
{   
    if(mSelectionPolicy){
    delete mSelectionPolicy;
    }
    mSelectionPolicy =nullptr;
}



Agent& Agent::operator=(const Agent& other)
{
    if(this != &other)
    {
    if(mSelectionPolicy){
        delete mSelectionPolicy;
    }
    mAgentId= other.mAgentId;
    mPartyId =other.mPartyId;
    mSelectionPolicy= other.mSelectionPolicy->copy() ;
    coalitionId= other.coalitionId;
    }

    return *this;
}

// move assignment operator
Agent& Agent::operator=(Agent&& other)
{
    if(mSelectionPolicy){
        delete mSelectionPolicy;
    }
    mSelectionPolicy = nullptr;
    mAgentId= other.mAgentId;
    mPartyId =other.mPartyId;
    mSelectionPolicy= other.mSelectionPolicy ;
    coalitionId= other.coalitionId;

    other.mSelectionPolicy=nullptr;
    
    return *this;
}

int Agent::getCoalitionId(){
    return coalitionId;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{

    std::vector<Party*> relevantParties;
    for (int i = 0; i < sim.getGraph().getNumVertices(); i++)
    {
        if (sim.getParty(i).getState() != Joined)
        {
            if (sim.getGraph().getEdgeWeight(mPartyId, i) != 0)
            {
                bool exist= false;
                for (int j=0 ; j<sim.getParty(i).getnumberOfOffers() && !exist ; j++){
                    if (sim.getParty(i).getOfferByAgentsAt(j).coalitionId == coalitionId){
                        exist = true;
                    }
                }
                if (!exist){
                    relevantParties.push_back(&(sim.getParty(i)));
                }
            }
        }
    }
    int id = mSelectionPolicy->select(relevantParties, sim, mPartyId);

    if (id!=-1){
        relevantParties.at(id)->collectOffer(*this);
    }
    
    
}
