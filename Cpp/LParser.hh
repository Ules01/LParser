#pragma once

#include "Graphe.hh"

using namespace std;

class LParser {
    public:
        explicit LParser(char *regexp);
        friend ostream& operator<<(ostream&, const LParser& lparser);

        Graphe graphe;
    private:
        char *regexp;

        Token token(shared_ptr<int> pos);
        void eat(shared_ptr<int> pos, Token search);
        static void misMatch(char get, Token expect, int start, int end);

        //Parser LL(1)
        void Z(shared_ptr<int> pos);
        Graphe S(shared_ptr<int> pos);
        Graphe A(shared_ptr<int> pos);
        Graphe B(shared_ptr<int> pos);
        Graphe C(shared_ptr<int> pos, Graphe graphe2);
        Graphe D(shared_ptr<int> pos);
        Graphe E(shared_ptr<int> pos, Graphe graphe2);
};
