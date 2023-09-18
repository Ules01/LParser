#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

class LParser {
    public:
        explicit LParser(char *regexp);
        friend ostream& operator<<(ostream&, const LParser& lparser);
    private:
        char *regexp;

        enum tok{
            OR,
            LPARA,
            RPARA,
            DOT,
            MB,
            EUCLIDE,
            PLUS,
            END,
            N,
        };

        class Token {
            public:
                char c;
                enum tok tok;

                Token(char c, enum tok tok);
                bool operator!=(char c) const;
                bool operator==(char c) const;
                bool in(const string& str) const;
        };

        Token token(shared_ptr<int> pos);
        void eat(shared_ptr<int> pos, Token search);
        static void misMatch(char get, LParser::Token expect, int start, int end);

        //Parser LL(1)
        void S(shared_ptr<int> pos);
        void A(shared_ptr<int> pos);
        void B(shared_ptr<int> pos);
        void C(shared_ptr<int> pos);
        void D(shared_ptr<int> pos);
        void E(shared_ptr<int> pos);
};
