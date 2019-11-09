#include "utils.h"

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
    clear_tree(root);
}

void TabuList::clear_tree(Node *node) {
    if (node != NULL) {
        for (Node* n : node->children) {
            clear_tree(n);
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

// bool TabuList::find_and_add(Solution s) {
//     Node *current;

//     current = root;
//     for (int i : s.config) {
//         bool stop = true;

//         if (i == -1) {
//             if (current->children[0]) {
//                 current = current->children[0];
//                 stop = false;
//             }
//         }
//         else {
//             if (current->children[i]) {
//                 current = current->children[i];
//                 stop = false;
//             }
//         }

//         if (stop) {
//             this->add(s);
//             return false;
//         }
//     }

//     if (current->depth > s.steps.size()) {
//         current->depth = s.steps.size();
//         return false;
//     }
//     else {
//         return true;
//     }    
// }

