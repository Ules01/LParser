#include "LParser.hh"

using namespace std;

LParser::LParser(char *regexp){
    this->regexp = regexp;
}
LParser::Token::Token(char c, enum LParser::tok tok) {
    this->c = c;
    this->tok = tok;
}

bool LParser::Token::operator!=(char c) {
    return c != this->c;
}

bool LParser::Token::operator==(char c) {
    return c == this->c;
}

LParser::Token LParser::token(int *pos)
{
    for (;*(this->regexp + *pos) == ' '; *pos += 1){}
    switch (*(this->regexp + *pos))
    {
        case '\0':
            return {'\0', LParser::END};
        case '+':
            return {'+', LParser::OR};
        case '(':
            return {'(' ,LParser::LPARA};
        case ')':
            return {')', LParser::RPARA};
        case '.':
            return {'.', LParser::DOT};
        case '?':
            return {'?', LParser::MB};
        case '*':
            return {'*', LParser::EUCLIDE};
        case '!':
            return {'!', LParser::PLUS};
        default:
            return {(*(this->regexp + *pos)), LParser::N};
    }
}

void LParser::eat(int *pos, LParser::Token search){
    int before = *pos;
    char tok = (*(this->regexp + *pos));
    if (search != tok)
        LParser::mis_match(tok, search, before, *pos);
    *pos += 1;
}

void LParser::mis_match(char get, LParser::Token expect, int start, int end){
    cerr << "Syntax error: was expecting " << expect.c << " but get " << get << endl;
}

