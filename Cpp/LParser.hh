#pragma once

#include "Token.hh"

using namespace std;

class LParser {
    public:
        explicit LParser(char *regexp);
        friend ostream& operator<<(ostream&, const LParser& lparser);
    private:
        char *regexp;

        Token token(shared_ptr<int> pos);
        void eat(shared_ptr<int> pos, Token search);
        static void misMatch(char get, Token expect, int start, int end);

        //Parser LL(1)
        void Z(shared_ptr<int> pos);
        void S(shared_ptr<int> pos);
        void A(shared_ptr<int> pos);
        void B(shared_ptr<int> pos);
        void C(shared_ptr<int> pos);
        void D(shared_ptr<int> pos);
        void E(shared_ptr<int> pos);
};
