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

void Graphe::subMerge(int n1, int n2) {
    for (auto link : this->G){
        this->G[n2][link.first] = this->G[n1][link.first];
    }
}

void Graphe::euclidePlus() {
    for (int e : this->end){
        for (auto link : this->G){
            this->G[e][link.first] = this->G[0][link.first];
        }
    }

}

void Graphe::mb() {
    this->end.insert(0);
}

void Graphe::euclide() {
    euclidePlus();
    mb();
}

void Graphe::operator*(Graphe graphe2) {
    int conv[graphe2.G.size()];
    for (int i = 0; i < graphe2.G.size(); i++){
        conv[i] = newNode();
    }
    char c;
    int n;
    for (const auto& link_1 : graphe2.G){
        for (auto link_2 : link_1.second){
           c = link_2.first;
           if (link_1.first == 0){
               for (int e : this->end){
                   if (this->G[e].find(c) != this->G[e].end()){
                        n = this->G[e][c];
                        this->G[e][c] = conv[graphe2.G[link_1.first][c]];
                        if (n != e){
                            subMerge(n, conv[graphe2.G[link_1.first][c]]);
                        } else {
                            this->G[conv[graphe2.G[link_1.first][c]]][c] = conv[graphe2.G[link_1.first][c]];
                        }
                   } else {
                       this->G[e][c] = conv[graphe2.G[link_1.first][c]];
                   }
               }
           } else {
               if (this->G[conv[link_1.first]].find(c) != G[conv[link_1.first]].end()){
                   n = this->G[conv[link_1.first]][c];
                   this->G[conv[link_1.first]][c] = conv[graphe2.G[link_1.first][c]];
                   if (n != conv[link_1.first]) {
                       subMerge(n, conv[graphe2.G[link_1.first][c]]);
                   } else {
                       this->G[conv[graphe2.G[link_1.first][c]]][c] = conv[graphe2.G[link_1.first][c]];
                   }
               } else {
                   this->G[conv[link_1.first]][c] = conv[graphe2.G[link_1.first][c]];
               }
           }
        }
    }
    set<int> newEnd = set<int>();
    for (int e2 : graphe2.end){
        if (e2 == 0){
            for (int e : this->end){
                newEnd.insert(e);
            }
        } else {
            newEnd.insert(conv[e2]);
        }
    }
    this->end = newEnd;
}

void Graphe::operator+(Graphe graphe2) {
    map<int, int> conv = map<int,int>({pair<int,int>(0,0)});
    char c;
    for (const auto& link_1 : graphe2.G){
        for (auto link_2 : link_1.second){
            c = link_2.first;
            if (this->G[conv[link_1.first]].find(c) != this->G[conv[link_1.first]].end()){
                conv[this->G[link_1.first][c]] = this->G[link_1.first][c];
            } else {
                if (conv.find(graphe2.G[link_1.first][c]) == conv.end()) {
                    conv[graphe2.G[link_1.first][c]] = newNode();
                }
            }
            this->G[conv[link_1.first]][c] = conv[graphe2.G[link_1.first][c]];
        }
    }
    for (int e2 : graphe2.end){
        this->end.insert(conv[e2]);
    }
}
