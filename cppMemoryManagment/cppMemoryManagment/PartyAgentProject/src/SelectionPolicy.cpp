#include "../include/SelectionPolicy.h"
#include "../include/Simulation.h"
#include "../include/Agent.h"
#include <vector>

using std::vector;





MandatesSelectionPolicy::MandatesSelectionPolicy(){}


MandatesSelectionPolicy* MandatesSelectionPolicy::copy(){
    MandatesSelectionPolicy* mjp= new MandatesSelectionPolicy();
    return mjp;
}


int MandatesSelectionPolicy::select(vector<Party*>& relevantParties, Simulation& sim, int agentPartyID)
{
    int highestMandates = 0;
    int highestMandatesId = -1;
    int currMandates = 0;
    int size = relevantParties.size();
    for (int i = 0; i <size ; i++)
    {
        currMandates = sim.getGraph().getMandates(relevantParties.at(i)->getId());            
        if (highestMandates < currMandates)
        {
            highestMandates = currMandates;
            highestMandatesId = i;
        }
    }
    return (highestMandatesId);
}

EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy() {}


EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::copy(){
    return new EdgeWeightSelectionPolicy();
}

int EdgeWeightSelectionPolicy::select(vector<Party*>& relevantParties, Simulation& sim, int agentPartyID)
{
    int highestweight = 0;
    int highestweightId = -1;
    int currWeight = 0;
    int size =relevantParties.size();
    for (int i=0 ; i < size; i++)
    {
        currWeight = sim.getGraph().getEdgeWeight(agentPartyID, relevantParties.at(i)->getId());            
        if (highestweight < currWeight){
            highestweight = currWeight;
            highestweightId = i;
        }
    }
    return (highestweightId);
};