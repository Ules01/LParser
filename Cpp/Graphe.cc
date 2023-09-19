//
// Created by jules on 18/09/23.
//

#include "Graphe.hh"

const map<int, map<char, int>>& Graphe::get(){
    return this->G;
}

Graphe::Graphe() {
    this->G[0] = map<char, int>();
    this->end.insert(0);
}

int Graphe::newNode() {
    int node = this->G.size();
    this->G[node] = map<char, int>();
    return node;
}

void Graphe::add(char c) {
    int node = newNode();
    while (this->end.size() > 0){
        int e = *this->end.begin();
        this->end.erase(e);
        this->G[e][c] = node;
    }
    this->end.insert(node);
}
