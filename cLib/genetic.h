#pragma once

#include <vector>
#include "utils.h"

const int SIMU_TIME = 100;

// ------------- Solution ------------- //
class Solution 
{
    private:
    void metamodel();

    public:
    static TabuList tabu;
    static int totalSimuNumber;

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
    void simulate();
};


// ------------- Genetic ------------- //
class Genetic 
{
    private:
    int genNumber;

    std::vector<Solution> population;
    int popSize;
    float popStd;

    public:
    Params bestSol;

    Genetic();

    void initial_pop(const char*);
    void run();
    void generation_step();
    void calc_std();
};