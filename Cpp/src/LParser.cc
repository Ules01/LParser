#include "LParser.hh"

using namespace std;

LParser::LParser(const string& regexp){
    this->regexp = new char [regexp.length() + 1];
    strcpy(this->regexp, regexp.c_str());
    this->graphe = Graphe();
    this->Z(make_shared<int>(0));
}

LParser::LParser(char *regexp) {
    this->regexp = regexp;
    this->graphe = Graphe();
    this->Z(make_shared<int>(0));
}

Token LParser::token(const shared_ptr<int>& pos) {
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

void LParser::eat(const shared_ptr<int>& pos, Token search){
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
    return os<<lparser.regexp << endl;
}

void LParser::Z(const shared_ptr<int>& pos) {
    Graphe graphe_tmp = this->S(pos, Graphe());
    this->eat(pos, {'$', Token::END});
    this->graphe = graphe_tmp.reduce();
}

Graphe LParser::S(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    if (not tok.in(vector<enum Token::tok>({Token::RPARA, Token::EUCLIDE, Token::MB, Token::PLUS, Token::OR, Token::END})))
        return this->A(pos, G);
    return G;
}

Graphe LParser::A(const shared_ptr<int>& pos, Graphe G) {
    Graphe G2 = this->B(pos, Graphe());
    G = G * G2;
    G = this->C(pos, G);
    return this->S(pos, G);
}

Graphe LParser::B(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    if (tok.tok == Token::LPARA){
        this->eat(pos, tok);
        G = this->A(pos, Graphe());
        this->eat(pos, {')', Token::RPARA});
    }
    else {
        G = this->D(pos, G);
    }
    return this->E(pos, G);
}

Graphe LParser::C(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    if (tok.tok == Token::OR){
        this->eat(pos, tok);
        G = G + this->A(pos, Graphe());
        G = this->C(pos, G);
    }
    return G;
}

Graphe LParser::D(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    if (tok.tok == Token::DOT){
        this->eat(pos, tok);
        return G * '.';
    } else{
        this->eat(pos, {'n', Token::N});
        return G * tok.c;
    }
}

Graphe LParser::E(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    switch(tok.tok){
        case Token::EUCLIDE:
            eat(pos, tok);
            G.euclide();
            break;
        case Token::MB:
            eat(pos, tok);
            G.mb();
            break;
        case Token::PLUS:
            eat(pos, tok);
            G.euclidePlus();
            break;
        default:
            break;
    }
    return G;
}

void LParser::printGraph() {this->graphe.print();}

const map<int, map<char, int>> &LParser::getGraph() {return this->graphe.get();}

bool LParser::isaccept(const char *str) {
    auto G = this->graphe.get();
    int p = 0;
    char c;
    for (int i = 0; str[i] != '\0'; i++){
        c = str[i];
        if (G[p].find(c) == G[p].end()) {
            if (G[p].find('.') != G[p].end()) {
                p = G[p]['.'];
            } else { return false; }
        } else { p = G[p][c];}
    }
    return this->graphe.inEnd(p);
}

bool LParser::isaccept(const string& str) {
    char *cstr= new char [str.length() + 1];
    strcpy(cstr, str.c_str());
    return isaccept(cstr);
}

void LParser::export_graphivz() {
    this->graphe.export_graphivz();
}
