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

Graphe Graphe::operator*(char c){
    int node = newNode();
    while (!this->end.empty()){
        int e = *this->end.begin();
        this->end.erase(e);
        this->G[e][c] = node;
    }
    this->end.insert(node);
    return *this;
}

void Graphe::subMerge(int n1, int n2) {
    for (auto link : this->G[n1]){
        this->G[n2][link.first] = this->G[n1][link.first];
    }
}

void Graphe::euclidePlus() {
    for (int e : this->end){
        for (auto link : this->G[0]){
            this->G[e][link.first] = this->G[0][link.first];
        }
    }

}

void Graphe::mb() {
    this->end.insert(0);
}

void Graphe::euclide() {
    this->euclidePlus();
    this->end.insert(0);
}

Graphe Graphe::operator*(Graphe graphe2) {
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
    return *this;
}

Graphe Graphe::operator+(Graphe graphe2) {
    map<int, int> conv = map<int,int>({pair<int,int>(0,0)});
    char c;
    for (const auto& link_1 : graphe2.G){
        for (auto link_2 : link_1.second){
            c = link_2.first;
            if (this->G[conv[link_1.first]].find(c) != this->G[conv[link_1.first]].end()){
                if (this->end.find(this->G[conv[link_1.first]][c]) == this->end.end())
                    conv[graphe2.G[link_1.first][c]] = this->G[link_1.first][c];
                else{
                    if (conv.find(graphe2.G[link_1.first][c]) == conv.end()) {
                        conv[graphe2.G[link_1.first][c]] = this->newNode();
                        graphe2.end.insert(graphe2.G[link_1.first][c]);
                    }
                }
            } else {
                if (conv.find(graphe2.G[link_1.first][c]) == conv.end()) {
                    conv[graphe2.G[link_1.first][c]] = this->newNode();
                }
            }
            this->G[conv[link_1.first]][c] = conv[graphe2.G[link_1.first][c]];
        }
    }
    for (int e2 : graphe2.end){
        this->end.insert(conv[e2]);
    }
    return *this;
}

Graphe Graphe::reduce() {
    vector<bool> seen = vector<bool>(this->G.size(), false);
    seen[0] = true;
    for (const auto& link_1 : this->G){
        for (auto link_2 : this->G[link_1.first]){
            seen[link_2.second] = true;
        }
    }

    int k = 0;
    map<int,map<char,int>> G2 = map<int,map<char,int>>();
    G2[0] = map<char, int>();
    vector<int> conv = vector<int>(this->G.size(), 0);
    for (int i = 1; i < this->G.size(); i++){
        conv[i] = i;
    }
    for (int i = 1; i < this->G.size(); i++){
        if (!seen[i]){
            conv[i] = -1;
            k += 1;
        } else {
            if (k > 0){
                conv[i] = i - k;
            }
            G2[conv[i]] = map<char, int>();
        }
    }
    char c;
    set<int> end2 = set<int>();
    for (int n = 0; n < this->G.size(); n++){
        if (seen[n]){
            if (this->end.find(n) != this->end.end()){
                end2.insert(conv[n]);
            }
            for (auto link_2 : this->G[n]){
                c = link_2.first;
                G2[conv[n]][c] = conv[link_2.second];
            }
        }
    }
    this->end = end2;
    this->G = G2;
    return *this;
}

void Graphe::print() {
    for (const auto& link_1 : this->G){
        printf("%d:\n", link_1.first);
        for (auto link_2 : link_1.second){
            printf("\t%c -> %d\n", link_2.first, link_2.second);
        }
    }

    printf("\nEnd node:\n");
    for (int n : this->end){
        printf("\t%d\n", n);
    }
}

bool Graphe::inEnd(int p) {return this->end.find(p) != this->end.end();}

void Graphe::export_graphivz() {
    vector<vector<string>> digraph = vector<vector<string>>();
    for (int i = 0; i < this->G.size(); i++){
        vector<string> sub = vector<string>();
        for (int j = 0; j < this->G.size(); j++){
            sub.emplace_back("");
        }
        digraph.emplace_back(sub);
    }

    for (auto link_1 : this->G){
        for (auto link_2 : link_1.second) {
            if (!digraph[link_1.first][link_2.second].empty()){
                digraph[link_1.first][link_2.second] += ", ";
            }
            digraph[link_1.first][link_2.second] += link_2.first;
        }
    }

    string exp = "digraph {\n\t{ node [shape=\"doublecircle\"];";
    for (int e: this->end){
        exp += " " + to_string(e) + ";";
    }
    exp += "}\n\tempty [label=\"\", shape=none]\n\tempty->0\n";

    for (int i = 0; i < digraph.size(); i++){
        for (int j = 0; j < digraph.size(); j++){
            if (!digraph[i][j].empty()){
                exp+= "\t" + to_string(i) + "->" + to_string(j) +" [ label=\"" + digraph[i][j] + "\" ]\n";
            }
        }
    }
    exp = exp + "}";
    cout << exp << endl;
}


Graphe Graphe::reduce_or(){

    set<int> to_del = set<int>();
    set<int> new_end = set<int>();
    for (int e: this->end){
        if (this->G[e].empty()) {
            to_del.insert(e);
        }

    }
    if (to_del.empty())
        return *this;
    map<int, int> conv = map<int,int>();
    int count = 0;
    int super_end = this->G.size() - to_del.size();
    for (int node = 0; node < this->G.size(); node++){
        if (to_del.find(node) == to_del.end()){
            conv[node] = count;
            count += 1;
        } else {
            conv[node] = super_end;
        }

    }
    Graphe res = Graphe();
    for (int i = 0; i < super_end; i++)
        res.newNode();
    for (auto link_1: this->G){
        for (auto link_2: link_1.second){
            res.G[conv[link_1.first]][link_2.first] = conv[link_2.second];
        }
    }
    for (int e: this->end)
        new_end.insert(conv[e]);

    res.end = new_end;
    return res;
}
