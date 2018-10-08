#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>

#include "node.h"
#include "state.h"
#include "action.h"

using namespace std;

struct Model {
    State boarding, unboarding;
    map<State, vector<pair<State, int>>> * cities;
    unordered_map<State, int> *sld;

    Model(State _boarding, State _unboarding, map<State, vector<pair<State, int>>> * _cities, unordered_map<State, int> *_sld) {
        boarding = _boarding;
        unboarding = _unboarding;
        cities = _cities;
        sld = _sld;
    }

    ~Model() {
        delete cities;
    }

    bool wasVisited(vector<State> *t, State s) {
        for(State elem : (*t)) {
            if(elem == s)
                return true;
        }
        return false;
    }

    Node * dfs() {

        stack<Node *> edg;
        vector<State> expl;

        edg.push(new Node( nullptr,
                           boarding,
                           new Action(boarding),
                           0,
                           0)); // the heuristic campus isn't used in this search

        while(!edg.empty()) {
            Node *current = edg.top();
            expl.push_back(current->s);
            edg.pop();

            for(pair<State, int> each : cities->at(current->s)) {
                Node *n = new Node(current,
                                   each.first,
                                   new Action(current->s, each.first),
                                   each.second + current->costPath,
                                   0); // the heuristic campus isn't used in this search

                if(n->s == unboarding) {
                    return n;
                }
                else {
                    if(!wasVisited(&expl, n->s)) {
                        edg.push(n);
                    }
                }
            }
        }

        return nullptr;
    }

    Node * bfs() {

        queue<Node *> edg;
        vector<State> expl;

        edg.push( new Node( nullptr,
                            boarding,
                            new Action(boarding),
                            0,
                            0)); // the heuristic campus isn't used in this search

        while(!edg.empty()) {
            Node * current = edg.front();
            edg.pop();

            expl.push_back(current->s);

            if(current->s == unboarding)
                return current;

            for(pair<State, int> each : cities->at(current->s)) {
                if(!wasVisited(&expl, each.first)) {
                    edg.push( new Node( current,
                                        each.first,
                                        new Action(current->s, each.first),
                                        each.second + current->costPath,
                                        0)); // the heuristic campus isn't used in this search
                }

            }
        }

        return nullptr;
    }

    Node * ucs() {
        priority_queue<Node *, vector<Node *>, Compar > edg;
        vector<State> expl;

        edg.push( new Node( nullptr,
                            boarding,
                            new Action(boarding),
                            0,
                            0));

        while(!edg.empty()) {
            Node * current = edg.top();
            edg.pop();

            expl.push_back(current->s);

            if(current->s == unboarding)
                return current;

            for(pair<State, int> each : cities->at(current->s)) {
                if(!wasVisited(&expl, each.first)) {
                    edg.push( new Node( current,
                                        each.first,
                                        new Action(current->s, each.first),
                                        each.second + current->costPath, 0));
                }

            }
        }

        return nullptr;
    }

    Node * searchGreedy() {

        priority_queue< Node *, vector<Node *>, HCompar> edg;
        vector<State> expl;

        edg.push( new Node( nullptr,
                            boarding,
                            new Action(boarding),
                            0,
                            sld->at(boarding)));

        while(!edg.empty()) {
            Node * current = edg.top();
            edg.pop();

            expl.push_back(current->s);

            if(current->s == unboarding)
                return current;

            for(pair<State, int> each : cities->at(current->s)) {
                if(!wasVisited(&expl, each.first)) {
                    edg.push( new Node( current,
                                        each.first,
                                        new Action(current->s, each.first),
                                        each.second + current->costPath,
                                        sld->at(current->s)));
                }

            }
        }
        return nullptr;
    }


    Node * starSearch() {

        priority_queue< Node *, vector<Node *>, HCompar> edg;
        vector<State> expl;

        edg.push( new Node( nullptr,
                            boarding,
                            new Action(boarding),
                            0,
                            sld->at(boarding)));

        while(!edg.empty()) {
            Node * current = edg.top();
            edg.pop();

            expl.push_back(current->s);

            if(current->s == unboarding)
                return current;

            for(pair<State, int> each : cities->at(current->s)) {
                if(!wasVisited(&expl, each.first)) {
                    edg.push( new Node( current,
                                        each.first,
                                        new Action(current->s, each.first),
                                        each.second + current->costPath,
                                        each.second + sld->at(current->s)));
                }

            }
        }
        return nullptr;
    }

};


#endif // MODEL_H
