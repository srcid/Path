#ifndef NODE_H
#define NODE_H

#include "state.h"
#include "action.h"

struct Node {
    Node *dad;
    State s;
    Action *a;
    int costPath;
    int hCostPath;

    Node(Node *_dad, State _s, Action *_a, int _cost, int _hCostPath) {
        dad = _dad;
        s = _s;
        a = _a;
        costPath = _cost;
        hCostPath = _hCostPath;
    }

    ~Node() {
        delete a;
    }

};

struct Compar {
    bool operator() (const Node *x, const Node *y) const {
        return x->costPath > y->costPath;
    }
};

struct HCompar {
    bool operator() (const Node *x, const Node *y) const {
        return x->hCostPath > y->hCostPath;
    }
};


#endif // NODE_H
