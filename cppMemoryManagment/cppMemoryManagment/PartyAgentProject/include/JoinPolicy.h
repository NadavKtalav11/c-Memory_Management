
#pragma once

class Simulation;
class Party;

class JoinPolicy 
{
public :
    JoinPolicy() = default;
    virtual ~JoinPolicy() = default;
    virtual void join(Simulation& , Party&) = 0;
    virtual JoinPolicy* copy() const = 0;
};



class MandatesJoinPolicy : public JoinPolicy 
{
public:

    virtual ~MandatesJoinPolicy() ;
    void join(Simulation &_sim , Party& party) override;
    virtual MandatesJoinPolicy* copy() const override;
};

class LastOfferJoinPolicy : public JoinPolicy 
{
public:

    virtual ~LastOfferJoinPolicy();
    void join(Simulation &_sim , Party& party)override;
    virtual LastOfferJoinPolicy* copy() const override;
};