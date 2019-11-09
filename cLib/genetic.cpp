//#include <vector>
#include <algorithm>
#include <iostream>
#include "genetic.h"
//#include "utils.h"


//----------- Solution -----------//
Solution::Solution(int s, int d, int o, int l) {
    sMin = s;
    sDiff = d;
    orderType = o;
    deliveryType = l;
    simulated = false;

    metamodel();    
}

Params Solution::get_params() {
    Params params;

    params.s = sMin;
    params.d = sDiff;
    params.o = orderType;
    params.l = deliveryType;

    params.hc = holdingCost;
    params.sc = shortageCost;
    params.oc = orderCost;
    params.inv = inviability;

    return params;
}

void Solution::metamodel() {
    holdingCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;
    shortageCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;
    orderCost = 1 + 1*sMin + 1*sDiff + 1*orderType + 1*deliveryType;
    
    totalCost = holdingCost + shortageCost + orderCost;
    inviability = (std::max(0.0f, shortageCost - 30) + std::max(0.0f, holdingCost - 100)) / 2; 
}

bool Solution::simulate(TabuList tabu) {
    simulated = true;
    Node* node = tabu.find(get_params());

    if (node) {
        holdingCost = node->holdingCost;
        shortageCost = node->shortageCost;
        orderCost = node->orderCost;
        totalCost = node->totalCost;
        inviability = node->inviability;
        return false;  
    }
    else {
        metamodel();
        tabu.add(get_params());
        return true;
    }   
}


//------------ Genetic ------------//
void Genetic::run() {
    while(true) {
        std::cout << "=======================================" << std::endl;
        std::cout << "-----> Generation: " << genNumber << std::endl;
        generation_step();
        std::cout << "Best solution:" << bestSol << std::endl;
        std::cout << "Num simulations (gen):" << simuNumber << std::endl;
        std::cout << "Num simutaions (total):" << totalSimuNumber << std::endl;
        std::cout << "Population std:" << popStd << std::endl;
    }
}

void Genetic::generation_step() {
    
}