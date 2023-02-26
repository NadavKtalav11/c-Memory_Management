#pragma once

#include <vector>

class Party;
class Simulation;
using std::vector;

class SelectionPolicy 
{ 
public:
    
    virtual ~SelectionPolicy() = default;
    virtual int select(vector<Party*>&, Simulation&, int) = 0;
    virtual SelectionPolicy* copy() = 0;
};

class MandatesSelectionPolicy: public SelectionPolicy
{ 
public:
    MandatesSelectionPolicy();

    int select(vector<Party*>&, Simulation&, int) override;
    MandatesSelectionPolicy* copy() override;

};

class EdgeWeightSelectionPolicy: public SelectionPolicy
{
public:
    EdgeWeightSelectionPolicy();
    int select(vector<Party*>&, Simulation&, int) override;
    EdgeWeightSelectionPolicy* copy() override;
};