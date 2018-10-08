#ifndef ACTION_H
#define ACTION_H

#include <string>

#include "state.h"

using namespace std;

struct Action {
    string act;

    Action(State boarding, State unboarding) {
        act = "From " + stateToString(boarding) + " to " + stateToString(unboarding);
    }

    Action(State begin) {
        act = "Begin in " + stateToString(begin);
    }
};


#endif // ACTION_H
