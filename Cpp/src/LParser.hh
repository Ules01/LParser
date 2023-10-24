#pragma once

#include <cstring>

#include "Graphe.hh"

using namespace std;

class LParser {
    public:
        explicit LParser(const string& regexp);
        explicit LParser(char *regexp);

        friend ostream& operator<<(ostream&, const LParser& lparser);

        void printGraph();
        bool isaccept(const char *str);
        bool isaccept(const string& str);

        void export_graphivz();
    const map<int, map<char, int>>& getGraph();
    private:
        char *regexp;
        Graphe graphe;
        Token token(const shared_ptr<int>& pos);
        void eat(const shared_ptr<int>& pos, Token search);
        static void misMatch(char get, Token expect, int start, int end);

        //Parser LL(1)
        void Z(const shared_ptr<int>& pos);
        Graphe S(const shared_ptr<int>& pos, Graphe G);
        Graphe A(const shared_ptr<int>& pos, Graphe G);
        Graphe B(const shared_ptr<int>& pos, Graphe G);
        Graphe C(const shared_ptr<int>& pos, Graphe G);
        Graphe D(const shared_ptr<int>& pos, Graphe G);
        Graphe E(const shared_ptr<int>& pos, Graphe G);
};
