#include <bits/stdc++.h>

#include "state.h"
#include "action.h"
#include "node.h"
#include "model.h"

using namespace std;

void printPath(Node *n) {

    if(n == nullptr)
        return;

    printPath(n->dad);

    cout << n->a->act << "; cost: " << n->costPath << endl;

    delete n;

    return;
}

void deletePath(Node *n) {

    Node *a;
    while(n != nullptr) {
        a = n;
        n = n->dad;
        delete[] a;
    }

    return;
}

void loadMap(map<State, vector<pair<State, int>>> *cities) {
    (*cities)[arad] = {make_pair(zerind, 75), make_pair(timisoara, 118), make_pair(sibiu, 140)};
    (*cities)[zerind] = {make_pair(arad, 75), make_pair(oradea, 71)};
    (*cities)[oradea] = {make_pair(zerind, 71), make_pair(sibiu, 151)};
    (*cities)[sibiu] = {make_pair(arad, 140), make_pair(fagaras, 99), make_pair(rimnicu, 80)};
    (*cities)[fagaras] = {make_pair(sibiu, 99), make_pair(bucharest, 211)};
    (*cities)[rimnicu] = {make_pair(sibiu, 80), make_pair(pitesti, 97), make_pair(craiova, 146)};
    (*cities)[pitesti] = {make_pair(rimnicu, 97), make_pair(craiova, 138), make_pair(bucharest, 101)};
    (*cities)[craiova] = {make_pair(drobeta, 120), make_pair(pitesti, 138), make_pair(rimnicu, 146)};
    (*cities)[drobeta] = {make_pair(mehadia, 75), make_pair(craiova, 120)};
    (*cities)[mehadia] = {make_pair(drobeta, 75), make_pair(lugoj, 70)};
    (*cities)[lugoj] = {make_pair(mehadia, 70), make_pair(timisoara, 111)};
    (*cities)[timisoara] = {make_pair(lugoj, 111), make_pair(arad, 118)};
    (*cities)[bucharest] = {make_pair(giurgiu, 90), make_pair(pitesti, 101), make_pair(urziceni, 85)};
    (*cities)[giurgiu] = {make_pair(bucharest, 90)};
    (*cities)[urziceni] = {make_pair(bucharest, 85), make_pair(hirsova, 98), make_pair(vaslui, 142)};
    (*cities)[hirsova] = {make_pair(urziceni, 98), make_pair(eforie, 86)};
    (*cities)[eforie] = {make_pair(hirsova, 86)};
    (*cities)[vaslui] = {make_pair(urziceni, 142), make_pair(iasi, 92)};
    (*cities)[iasi] = {make_pair(vaslui, 92), make_pair(neamt, 87)};
    (*cities)[neamt] = {make_pair(iasi, 87)};

    return;
}

void loadHashTable(unordered_map<State, int> *sld) {
    (*sld)[arad] = 366;
    (*sld)[bucharest] = 0;
    (*sld)[craiova] = 160;
    (*sld)[drobeta] = 242;
    (*sld)[eforie] = 161;
    (*sld)[fagaras] = 176;
    (*sld)[giurgiu] = 77;
    (*sld)[hirsova] = 151;
    (*sld)[iasi] = 226;
    (*sld)[lugoj] = 244;
    (*sld)[mehadia] = 241;
    (*sld)[neamt] = 234;
    (*sld)[oradea] = 380;
    (*sld)[pitesti] = 100;
    (*sld)[rimnicu] = 193;
    (*sld)[sibiu] = 253;
    (*sld)[timisoara] = 329;
    (*sld)[urziceni] = 80;
    (*sld)[vaslui] = 199;
    (*sld)[zerind] = 374;

    return;
}

int main(int argc, char const *argv[])
{
    if(argc < 3) {
        cout << "few entries" << endl;
        return 0;
    }

    if(argc > 3) {
        cout << "many entries" << endl;
        return 0;
    }

    map<State, vector<pair<State, int>>> *cities = new map<State, vector<pair<State, int>>>();
    loadMap(cities);

    unordered_map<State, int> *sld = new unordered_map<State, int>;
    loadHashTable(sld);

    State boarding = stringToState(argv[1]), unboarding = stringToState(argv[2]);

    Model *model = new Model(boarding, unboarding, cities, sld);
    
    Node * deapth = model->dfs();
    Node * breadth = model->bfs();
    Node * uniform = model->ucs();
    Node * star = model->starSearch();
    Node * greedy = model->searchGreedy();

    cout << "DEAPTH-FIRST SEARCH" << endl << endl;
    printPath(deapth);
    cout << endl << "BREADTH-FIRST SEARCH" << endl << endl;
    printPath(breadth);
    cout << endl << "MINIMAL COST SEARCH" << endl << endl;
    printPath(uniform);
    cout << endl << "SEARCH GREEDY OF BETTER CHOICE" << endl << endl;
    printPath(greedy);
    cout << endl << "STAR SEARCH" << endl << endl;
    printPath(star);

    delete model;
    delete cities;
    delete sld;

    return 0;
}
