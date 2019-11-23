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

    double holdingCost;
    double shortageCost;
    double orderCost;
    double totalCost;
    double inviability;

    Solution(int, int, int, int);

    Params get_params();
    void simulate();
};


// ------------- Genetic ------------- //
class Genetic
{
    private:
    int genNumber;
    double elapsed;

    HiperParams hp;

    std::vector<Solution> population;
    double popStd;

    public:
    Params bestSol;

    Genetic(const char*, HiperParams = HiperParams());

    void initial_pop(const char*);
    void run();
    void generation_step();
    void calc_std();
    bool x1(Solution&, Solution&);
    std::vector<Solution> tournament();
    void reproduction();
    void armagedon();
};
