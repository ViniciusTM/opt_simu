#pragma once

#include <vector>
#include <limits>
#include <iostream>

const double D_INF = std::numeric_limits<double>::infinity();

//------------ Params ------------//
struct Params
{
    int s;      // estoque minimo
    int d;      // diferenca de estoque min e max
    int o;      // tipo de ordem
    int l;      // tipo de entrega

    double hc;   // custo de estoque
    double sc;   // custo de ruptura
    double oc;   // custo de pedido
    double ct;   // custo total
    double inv;  // inviabilidade
};

struct HiperParams
{
    int popSize;
    double stdTreshold;
    int itTreshold;
    double timeTreshold;
    double slackTreshold;
    double elitism;

    HiperParams(double = D_INF, int = RAND_MAX, double = 3, double = 5, double = 0.1);
};

// ------------- Tabu List ------------- //
struct Node {
    std::vector<Node*> children;

    double holdingCost;
    double shortageCost;
    double orderCost;
    double totalCost;
    double inviability;

    Node(int);
};

class TabuList {
    private:

    void recursive_clear(Node*);

    public:
    Node *root;
    int successes;
    int length;

    TabuList();
    ~TabuList();

    void clear();
    Node* find(Params);
    void add(Params);
};
