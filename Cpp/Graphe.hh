//
// Created by jules on 18/09/23.
//
#pragma once

#include "Token.hh"

class Graphe {
public:
        Graphe();
        Graphe operator +(Graphe graphe2);
        Graphe operator *(Graphe graphe2);
        Graphe operator *(char tok);

    void euclide();
        void mb();
        void euclidePlus();
        const map<int, map<char, int>>& get();
        Graphe reduce();

    private:
        map<int, map<char, int>> G;
        set<int> end;

        int newNode();
        void subMerge(int n1, int n2);
};