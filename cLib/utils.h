#pragma once 

#include <vector>

//------------ Params ------------//
struct Params {
    int s;      // estoque minimo
    int d;      // diferenca de estoque min e max
    int o;      // tipo de ordem 
    int l;      // tipo de entrega

    float hc;   // custo de estoque
    float sc;   // custo de ruptura
    float oc;   // custo de pedido
    float inv;  // inviabilidade
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
    void resursive_clear(Node*);

    public:
    int successes;
    int length;

    TabuList();
    ~TabuList();

    void clear();
    Node* find(Params);
    void add(Params);
};