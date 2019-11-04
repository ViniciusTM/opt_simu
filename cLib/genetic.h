#pragma once 

struct Solution {
    bool simutated;

    float holdingCost;
    float shortageCost;
    float orderCost;

    float inviability;

    int orderType;
    int deliveryType;
    int sMin;
    int sDiff;

    Solution(int, int, int, int);
    ~Solution();

    void simulate();
    void methamodel();
}