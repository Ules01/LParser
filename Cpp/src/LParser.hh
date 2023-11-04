#pragma once

#include <cstring>

#include "Graphe.hh"

using namespace std;

#define VALUE_ERROR (1)
#define SYNTAX_ERROR (2)

class LParser {
    public:
        explicit LParser(const string& regexp);
        explicit LParser(char *regexp);
        friend ostream& operator<<(ostream&, const LParser& lparser);
        void printGraph();
        bool isaccept(const char *str);
        bool isaccept(const string& str);
        char * found(const char *str);
        char * found(const char *str, size_t pos);
        vector<string> all(const char *str);
        vector<string> all_at(const char *str, size_t pos);
        void export_parserC();


    void export_graphivz();
    const map<int, map<char, int>>& getGraph();
    private:
        char *regexp;
        Graphe graphe;
        Token token(const shared_ptr<int>& pos);
        void eat(const shared_ptr<int>& pos, Token search);
        static void misMatch(char get, Token expect);
        pair<int, char *> subfound(const char* str, int pos);

        //Parser LL(1)
        void Z(const shared_ptr<int>& pos);
        Graphe S(const shared_ptr<int>& pos, Graphe G);
        Graphe A(const shared_ptr<int>& pos, Graphe G);
        Graphe B(const shared_ptr<int>& pos, Graphe G);
        Graphe C(const shared_ptr<int>& pos, Graphe G);
        Graphe D(const shared_ptr<int>& pos, Graphe G);
        Graphe E(const shared_ptr<int>& pos, Graphe G);
        Graphe F(const shared_ptr<int>& pos, Graphe G);
};
