#include "../include/Party.h"
#include "../include/JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) ,  coalitionId(0) , coolDown(0), offersByAgents()

{
    
}

// copy constructor
Party::Party(const Party& other):
mId(other.mId),mName (other.mName) ,mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->copy()),mState(other.mState),coalitionId(other.coalitionId), coolDown(other.coolDown),offersByAgents(other.offersByAgents)
{
    
}

// move constructor
Party::Party(Party&& other) : 
mId(other.mId),mName (other.mName) ,mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState) ,coalitionId(other.coalitionId), coolDown(other.coolDown),offersByAgents(other.offersByAgents)

{  
   offersByAgents.clear();   
   other.mJoinPolicy = nullptr;

}


Party::~Party()
{
    if (mJoinPolicy){
       delete mJoinPolicy;
    }
    mJoinPolicy = nullptr;
}

Party& Party::operator=(const Party& other)
{
    if(this != &other)
    {
        if (mJoinPolicy){
            delete mJoinPolicy;
        }
        mJoinPolicy= nullptr;
        coolDown= other.coolDown;
        mId = other.mId;
        mName = other.mName;
        mJoinPolicy = other.mJoinPolicy->copy();
        mState = other.mState;
        coalitionId=other.coalitionId;
        offersByAgents =other.offersByAgents;

    }

    return *this;
}

// move assignment operator
Party& Party::operator=(Party&& other)
{
    if(mJoinPolicy){
        delete mJoinPolicy;
    }
    mJoinPolicy=nullptr;
    mId=other.mId;
    mName =other.mName;
    mJoinPolicy = other.mJoinPolicy;
    mState=other.mState;
    coalitionId=other.coalitionId;
    coolDown = other.coolDown;
    offersByAgents= other.offersByAgents;
    other.mJoinPolicy=nullptr;
    return *this;
}


int Party::getId() const
{
    return mId;
}

State Party::getState() const
{
    return mState;
}

void Party::setCoalitionId(int id){
    coalitionId = id;
}



void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}
Agent& Party::getOfferByAgentsAt(int i){
    return offersByAgents.at(i);
}
int Party::getOfferByAgentsSize(){
    return offersByAgents.size();
}


int Party::getLastPartyToJoin()
{
    int lastAgent = offersByAgents.at(offersByAgents.size()-1).getId();
    return (lastAgent);
}


const int Party::getCoalition() const
{
    return coalitionId;
}

void Party::collectOffer(Agent& agent )
{
    offersByAgents.push_back(agent);
    mState = CollectingOffers;
    if (coolDown==0){
    coolDown = 4;
    }
 
}
int Party::getnumberOfOffers( )
{
    return offersByAgents.size();  
}

void Party::step(Simulation &s)
{
    if (this->getState()==CollectingOffers){
        coolDown--;
    }
    if (coolDown ==1){
        mJoinPolicy->join(s ,*this);
        mState = Joined;
        coolDown =0;
    }


}
