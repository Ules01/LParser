#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

class LParser {
    public:
        LParser(char *regexp);

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
                bool operator!=(char c);
                bool operator==(char c);
        };

        Token token(int *pos);
        void eat(int *pos, Token search);
        void mis_match(char get, Token expect, int start, int end);

};
