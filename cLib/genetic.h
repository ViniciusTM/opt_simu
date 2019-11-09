#pragma once 

class Solution {
    public:
    int orderType;
    int deliveryType;
    int sMin;
    int sDiff;

    bool simutated;

    float holdingCost;
    float shortageCost;
    float orderCost;
    float totalCost;
    float inviability;

    Solution(int, int, int, int);
    ~Solution();

    void simulate();
    void methamodel();
}

class Genetic {
    private:
    int pop_size;
    float pop_std;
    std::vector<Solution> population;   

    public:
    float best_sol;

    Genetic();
    ~Genetic();    

    void initial_pop(const char*);
    void run();
    void generation_step();
    void calc_std(); 
    
}
