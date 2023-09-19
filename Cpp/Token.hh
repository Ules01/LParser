//
// Created by jules on 18/09/23.
//
#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <vector>

using namespace std;

class Token {
    public:
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

        char c;
        enum tok tok;

        Token(char c, enum tok tok);
        bool operator!=(Token token) const;
        bool operator==(char c) const;
        bool in(vector<enum tok> tokList) const;
};


