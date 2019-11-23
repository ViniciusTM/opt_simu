#pragma once

#include <vector>
#include <fstream>
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
    void report();
    void simulate();
};


// ------------- Genetic ------------- //
class Genetic
{
    private:
    int genNumber;
    std::ofstream reportFile;

    double elapsed;

    HiperParams hp;

    std::vector<Solution> population;
    double popStd;

    public:
    Params bestSol;

    Genetic(const char*, bool = false, HiperParams = HiperParams());

    void initial_pop(const char*);
    void run();
    void generation_step();
    void calc_std();
    int calc_viability();
    bool x1(Solution&, Solution&);
    std::vector<Solution> tournament();
    void reproduction();
    void armagedon();
    void report(double);
    void summary_print();
};
