#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <utility>

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


#endif // STATE_H
