#include "utils.h"

// ------------- HiperParams ------------- //
HiperParams::HiperParams(double st, int it, double tt, double slt)
{
    stdTreshold = st;
    itTreshold = it;
    timeTreshold = tt;
    slackTreshold = slt;
}

// ------------- Tabu List ------------- //
Node::Node(int n) {
    for (int i=0; i<n; i++) {
        children.push_back(NULL);
    }
}

TabuList::TabuList() {
    root = new Node(201);
    length = 0;
    successes = 0;
}

TabuList::~TabuList() {
    clear();
}

void TabuList::clear() {
    resursive_clear(root);
    successes = 0;
    length = 0;
}

void TabuList::resursive_clear(Node *node) {
    if (node != NULL) {
        for (Node* n : node->children) {
            resursive_clear(n);
        }
        delete node;
    }
}

Node* TabuList::find(Params params) {
    Node *current;

    current = root;
    if (!current->children[params.s - 50]) {
        return NULL;
    }

    current = current->children[params.s -50];
    if (!current->children[params.d - 10]) {
        return NULL;
    }

    current = current->children[params.d -10];
    if (!current->children[params.o - 1]) {
        return NULL;
    }

    current = current->children[params.o -1];
    if (!current->children[params.l - 1]) {
        return NULL;
    }

    current = current->children[params.l - 1];
    successes += 1;
    return current;
}

void TabuList::add(Params params) {
    Node *current;

    current = root;
    if (!current->children[params.s - 50]) {
        current->children[params.s - 50] = new Node(101);
    }

    current = current->children[params.s -50];
    if (!current->children[params.d - 10]) {
        current->children[params.d - 10] = new Node(10);
    }

    current = current->children[params.d -10];
    if (!current->children[params.o - 1]) {
        current->children[params.o - 1] = new Node(10);
    }

    current = current->children[params.o -1];
    if (!current->children[params.l - 1]) {
        current->children[params.l - 1] = new Node(0);
    }

    current = current->children[params.l - 1];
    current->holdingCost = params.hc;
    current->shortageCost = params.sc;
    current->orderCost = params.oc;
    current->totalCost = params.oc + params.sc + params.hc;
    current->inviability = params.inv;

    length += 1;
}
