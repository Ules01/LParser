//
// Created by jules on 18/09/23.
//

#include "Token.hh"

Token::Token(char c, enum tok tok) {
    this->c = c;
    this->tok = tok;
}


bool Token::operator==(char c) const {
    return c == this->c;
}

bool Token::operator!=(Token token) const {
    return token.tok != this->tok;
}


bool Token::in(const vector<enum tok> tokList) const {
    for (enum tok tok : tokList) {
        if (tok == this->tok)
            return true;
    }
    return false;
}