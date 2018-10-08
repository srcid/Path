#include <bits/stdc++.h>

using namespace std;

enum State { arad = 0, zerind, oradea, sibiu, fagaras, rimnicu, pitesti, craiova,  drobeta, mehadia, lugoj,
       timisoara, bucharest, giurgiu, urziceni, hirsova, eforie, vaslui, iasi, neamt };

string stateToString(State c) {
    switch(c) {
    case arad:
        return "Arad";
    case zerind:
        return "Zerind";
    case oradea:
        return "Oradeia";
    case sibiu:
        return "Sibiu";
    case fagaras:
        return "Fagaras";
    case rimnicu:
        return "Rimnincu Vilcea";
    case pitesti:
        return "Pitesti";
    case craiova:
        return "Craiova";
    case drobeta:
        return "Drobeta";
    case mehadia:
        return "Mehadia";
    case lugoj:
        return "Logoj";
    case timisoara:
        return "Timisoara";
    case bucharest:
        return "Bucharest";
    case giurgiu:
        return "Giurgiu";
    case urziceni:
        return "Urzicent";
    case hirsova:
        return "Hisova";
    case eforie:
        return "Eforie";
    case vaslui:
        return "Vaslui";
    case iasi:
        return "Iasi";
    case neamt:
        return "Neamt";
    default:
        return "no entry";
    }
}

State stringToState(string s) {
    if(s == "Arad" || s == "arad")
        return arad;
    if(s == "Zerind" || s == "zerind")
        return zerind;
    if(s == "Oradea" || s == "oradea")
        return oradea;
    if(s == "Sibiu"  || s == "sibiu")
        return sibiu;
    if(s == "Fagaras" || s == "fagaras")
        return fagaras;
    if(s == "Rimnicu Vilcea" || s == "rimnicu")
        return rimnicu;
    if(s == "Pitesti" || s == "pitesti")
        return pitesti;
    if(s == "Cravoia" || s == "cravoia")
        return craiova;
    if(s == "Drobeta" || s == "drobeta")
        return drobeta;
    if(s == "Mehadia" || s == "mehadia")
        return mehadia;
    if(s == "Lugoj" || s == "lugoj")
        return lugoj;
    if(s == "Timisoara" || s == "timisoara")
        return timisoara;
    if(s == "Bucharest" || s == "bucharest")
        return bucharest;
    if(s == "Giurgiu" || s == "giurgiu")
        return giurgiu;
    if(s =="Urziceni" || s == "urziceni")
        return urziceni;
    if(s == "Hirsova" || s == "hirsova")
        return hirsova;
    if(s == "Eforie" || s == "eforie")
        return eforie;
    if(s == "Vaslui" || s == "vaslue")
        return vaslui;
    if(s == "Iasi" || s == "iasi")
        return iasi;
    if(s == "Neamt" || s == "neamt")
        return neamt;

    cout << "entrada inválida." << endl;
    exit(0);
}

void printTowns(vector<pair<State, int>> v) {
    for(pair<State, int> p : v)
        cout << "Cidade: " << stateToString(p.first) << endl << "Distância: " << p.second << endl;
    return;
}

void printTown(pair<State, int> p) {
    cout << "Cidade: " << stateToString(p.first) << endl << "Distância: " << p.second << endl;
    return;
}

struct Action {
    string act;

    Action(State boarding, State unboarding) {
        act = "From " + stateToString(boarding) + " to " + stateToString(unboarding);
    }

    Action(State begin) {
        act = "Begin in " + stateToString(begin);
    }
};

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
