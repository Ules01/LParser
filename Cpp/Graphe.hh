//
// Created by jules on 18/09/23.
//
#pragma once

#include "Token.hh"

class Graphe {
public:
        Graphe();
        void mergeAdd();
        void mergeOr();
        void euclide();
        void mb();
        void euclidePlus();
        const map<int, map<char, int>>& get();
        void reduce();

    private:
        map<int, map<char, int>> G;
        set<int> end;

        int newNode();
        void add(char tok);
        void subMerge(int n1, int n2);
};