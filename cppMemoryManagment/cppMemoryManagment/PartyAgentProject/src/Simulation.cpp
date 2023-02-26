#include "../include/Simulation.h"
#include "../include/Graph.h"
#include "../include/Agent.h"
#include <vector>

using std::vector;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitions(), mandatesByCoalition()
{
    // You can change the implementation of the constructor, but not the signature!
}

void Simulation::step()
{

    int numOfVer = mGraph.getNumVertices();
    for(int i=0 ; i< numOfVer; i++)
    {
        mGraph.getParty(i).step(*this);

    }
    int size = mAgents.size();
    for (int j=0 ; j < size; j++)
    {
        mAgents.at(j).step(*this);

    }
}

    Party& Simulation::getParty(int partyId){
        return getGraph().getParty(partyId);
    } 

    Graph& Simulation::getGraph(){
        return mGraph;
    }
    



bool Simulation::shouldTerminate() const
{
    int size = coalitions.size();
    // TODO implement this method
    for (int i=0; i<size; i++){
        if (getTotalCoalitionMandates(i)>60){
            return true;
        }
    }
    return mGraph.sholdTerminate();
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Agent& Simulation::getAgent(int agentId)
{
    int size = mAgents.size();
    bool found= false;
    int id =-1;
    for (int i=0; i< size && !found; i++)
    {
        if (mAgents.at(i).getId()==agentId){
            found = true;
            id=i;
        }
    }
    return mAgents.at(id);
}


 void Simulation::addPartyToCoalition(int AgentId , int partyId){
    int coalitionId = mAgents.at(AgentId).getCoalitionId();
    coalitions.at(coalitionId).push_back(partyId);
    int mandatesBefore = mandatesByCoalition.at(coalitionId);
    int partyMandates = getGraph().getParty(partyId).getMandates();
    mandatesByCoalition.at(coalitionId)= partyMandates+mandatesBefore;
 }

 void Simulation::clone(int agentId , int partyId)
 {
    Agent agentToClone = getAgent(agentId);
    Agent agent = Agent(agentToClone ,mAgents.size(), partyId);
    mAgents.push_back(agent);
 }

 void Simulation::addFirstCoalitions(){
    int size =mAgents.size();
    for (int i=0 ; i<size; i++){
        vector<int> currVector;
        getParty(mAgents.at(i).getPartyId()).setCoalitionId(i);
        mandatesByCoalition.push_back(getParty(mAgents.at(i).getPartyId()).getMandates());
        currVector.push_back(mAgents.at(i).getPartyId());
        coalitions.push_back(currVector);
    }
 }

 const int Simulation::getTotalCoalitionMandates(int coalitionId) const 
 {

    return mandatesByCoalition.at(coalitionId);

 }


/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    return coalitions;
    
}
