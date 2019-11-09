#pragma once 

#include <vector>
#include "utils.h"

const int SIMU_TIME = 100;

// ------------- Solution ------------- //
class Solution {
    public:
    int sMin;
    int sDiff;
    int orderType;
    int deliveryType;

    bool simulated;

    float holdingCost;
    float shortageCost;
    float orderCost;
    float totalCost;
    float inviability;

    Solution(int, int, int, int);

    Params get_params();
    void metamodel();
    bool simulate(TabuList);
};


// ------------- Genetic ------------- //
class Genetic {
    private:    
    int genNumber;
    TabuList tabu;
    
    std::vector<Solution> population;
    int popSize;
    float popStd;

    int simuNumber;
    int totalSimuNumber;

    public:
    float bestSol;

    Genetic();  

    void initial_pop(const char*);
    void run();
    void generation_step();
    void calc_std(); 
    
};
