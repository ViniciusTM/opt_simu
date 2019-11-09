#pragma once 

#include <vector>

//------------ Params ------------//
struct Params {
    int s;
    int d;
    int o;
    int l;

    float hc;
    float sc;
    float oc;
    float inv;
};

// ------------- Tabu List ------------- //
struct Node {
    std::vector<Node*> children;
    float holdingCost;
    float shortageCost;
    float orderCost;
    float totalCost;
    float inviability;

    Node(int);
};

class TabuList {
    private:
    Node *root;

    public:
    int successes;
    int length;

    TabuList();
    ~TabuList();

    void clear_tree(Node*);
    Node* find(Params);
    void add(Params);
    // bool find_and_add(Solution s);
};