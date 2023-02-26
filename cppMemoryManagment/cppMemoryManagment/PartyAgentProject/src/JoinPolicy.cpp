#include "../include/JoinPolicy.h"
#include <algorithm>
#include "../include/Simulation.h"
#include "../include/Party.h"



MandatesJoinPolicy::~MandatesJoinPolicy(){}

MandatesJoinPolicy* MandatesJoinPolicy::copy() const{
    return new MandatesJoinPolicy(*this);
}
void MandatesJoinPolicy ::join(Simulation& sim, Party& party)
{
    vector <int> v  ;
    int highestMandates = 0;
   
    int highestCoalId = 0;
    int size =party.getOfferByAgentsSize();
    for (int i=0 ; i< size ; i++){
        int currMandates = sim.getTotalCoalitionMandates(party.getOfferByAgentsAt(i).getCoalitionId());
       if (currMandates >highestMandates){
        highestCoalId = i;
        highestMandates = currMandates;
       }
    }
    sim.addPartyToCoalition(party.getOfferByAgentsAt(highestCoalId).getCoalitionId() , party.getId() ); 
    sim.clone(party.getOfferByAgentsAt(highestCoalId).getId(), party.getId());

}



LastOfferJoinPolicy::~LastOfferJoinPolicy(){}

LastOfferJoinPolicy* LastOfferJoinPolicy::copy() const{
    return new LastOfferJoinPolicy(*this);
}



void LastOfferJoinPolicy ::join(Simulation &sim , Party& party){
    int idOfTheAgent = party.getLastPartyToJoin();
    sim.addPartyToCoalition(idOfTheAgent, party.getId() );
    sim.clone(idOfTheAgent, party.getId());
}
