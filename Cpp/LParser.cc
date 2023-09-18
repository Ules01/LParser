#include "LParser.hh"

using namespace std;

LParser::LParser(char *regexp){
    this->regexp = regexp;
}
LParser::Token::Token(char c, enum LParser::tok tok) {
    this->c = c;
    this->tok = tok;
}

bool LParser::Token::operator!=(char c) const {
    return c != this->c;
}

bool LParser::Token::operator==(char c) const {
    return c == this->c;
}

bool LParser::Token::in(const string& str) const {
    for (char c: str) {
        if (c == this->c)
            return true;
    }
    return false;
}

LParser::Token LParser::token(shared_ptr<int> pos)
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

void LParser::eat(shared_ptr<int> pos, LParser::Token search){
    int before = *pos;
    char tok = (*(this->regexp + *pos));
    if (search != tok)
        LParser::misMatch(tok, search, before, *pos);
    *pos += 1;
}

void LParser::misMatch(char get, LParser::Token expect, int start, int end){
    cerr << "Syntax error: was expecting " << expect.c << " but get " << get << endl;
}

ostream& operator<<(ostream& os, const LParser &lparser) {
    return os<<lparser.regexp;
}

void LParser::S(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.in(")!?*+$"))
        this->A(pos);
}

void LParser::A(shared_ptr<int> pos) {
    this->B(pos);
    this->C(pos);
    this->S(pos);
}

void LParser::B(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.tok == LPARA){
        this->eat(pos, {'(', LPARA});
        this->A(pos);
        this->eat(pos, {')', RPARA});
    }
    else {
        this->D(pos);
    }
}

void LParser::C(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.tok == OR){
        this->eat(pos, {'+', OR});
        this->B(pos);
        this->C(pos);
    }
}

void LParser::D(shared_ptr<int> pos) {

}

void LParser::E(shared_ptr<int> pos) {

}


int main(){
    LParser lParser = LParser("coucou");
    cout << "Hello wolrd!";
    cout << lParser;
}