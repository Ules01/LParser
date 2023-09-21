#include "LParser.hh"

using namespace std;

LParser::LParser(char *regexp){
    this->regexp = regexp;
    this->Z(make_shared<int>(0));
}

Token LParser::token(shared_ptr<int> pos) {
    for (; *(this->regexp + *pos) == ' '; *pos += 1) {}
    switch (*(this->regexp + *pos)) {
        case '\0':
            return {'$', Token::END};
        case '+':
            return {'+', Token::OR};
        case '(':
            return {'(', Token::LPARA};
        case ')':
            return {')', Token::RPARA};
        case '.':
            return {'.', Token::DOT};
        case '?':
            return {'?', Token::MB};
        case '*':
            return {'*', Token::EUCLIDE};
        case '!':
            return {'!', Token::PLUS};
        default:
            return {(*(this->regexp + *pos)), Token::N};
    }
}

void LParser::eat(shared_ptr<int> pos, Token search){
    int before = *pos;
    Token tok = this->token(pos);
    if (search != tok)
        LParser::misMatch(tok.c, search, before, *pos);
    *pos += 1;
}

void LParser::misMatch(char get, Token expect, int start, int end){
    cerr << "Syntax error: was expecting '" << expect.c << "' but get '" << get << "'" <<endl;
}

ostream& operator<<(ostream& os, const LParser &lparser) {
    return os<<lparser.regexp;
}

void LParser::Z(shared_ptr<int> pos) {
    this->S(pos);
    this->eat(pos, {'$', Token::END});
}

void LParser::S(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (not tok.in(vector<enum Token::tok>({Token::RPARA, Token::EUCLIDE, Token::MB, Token::PLUS, Token::OR, Token::END})))
        this->A(pos);
}

void LParser::A(shared_ptr<int> pos) {
    this->B(pos);
    this->C(pos);
    this->S(pos);
}

void LParser::B(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.tok == Token::LPARA){
        this->eat(pos, tok);
        this->A(pos);
        this->eat(pos, {')', Token::RPARA});
    }
    else {
        this->D(pos);
    }
    this->E(pos);
}

void LParser::C(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.tok == Token::OR){
        this->eat(pos, tok);
        this->B(pos);
        this->C(pos);
    }
}

void LParser::D(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (tok.tok == Token::DOT){
        this->eat(pos, tok);
    } else{
        this->eat(pos, {'n', Token::N});
    }
}

void LParser::E(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    switch(tok.tok){
        case Token::EUCLIDE:
            eat(pos, tok);
            break;
        case Token::MB:
            eat(pos, tok);
            break;
        case Token::PLUS:
            eat(pos, tok);
            break;
    }
}



int main(){
    map<int, int> M = map<int,int>();
    M[0] = 0;
    if (M.find(1) != M.end())
        cout << "Hello World" << endl;

}