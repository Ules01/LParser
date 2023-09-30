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
    Graphe graphe_tmp = this->S(pos);
    this->eat(pos, {'$', Token::END});
    this->graphe = graphe_tmp.reduce();
}

Graphe LParser::S(const shared_ptr<int>& pos) {
    Token tok = this->token(pos);
    if (not tok.in(vector<enum Token::tok>({Token::RPARA, Token::EUCLIDE, Token::MB, Token::PLUS, Token::OR, Token::END})))
        return this->A(pos);
    return {};
}

Graphe LParser::A(const shared_ptr<int>& pos) {
    Graphe graphe2 = this->B(pos);
    graphe2 = this->C(pos, graphe2);
    Graphe graphe3 = this->S(pos);
    return graphe2 * graphe3;
}

Graphe LParser::B(const shared_ptr<int>& pos) {
    Token tok = this->token(pos);
    Graphe graphe2;
    if (tok.tok == Token::LPARA){
        this->eat(pos, tok);
        graphe2 = this->A(pos);
        this->eat(pos, {')', Token::RPARA});
    }
    else {
        graphe2 = this->D(pos);
    }
    return this->E(pos, graphe2);
}

Graphe LParser::C(const shared_ptr<int>& pos, Graphe graphe2) {
    Token tok = this->token(pos);
    if (tok.tok == Token::OR){
        this->eat(pos, tok);
        graphe2 + this->B(pos);
        graphe2 = this->C(pos, graphe2);
    }
    return graphe2;
}

Graphe LParser::D(const shared_ptr<int>& pos) {
    Token tok = this->token(pos);
    Graphe graphe2 = Graphe();
    if (tok.tok == Token::DOT){
        this->eat(pos, tok);
        return graphe2 * '.';
    } else{
        this->eat(pos, {'n', Token::N});
        return graphe2 * tok.c;
    }
}

Graphe LParser::E(const shared_ptr<int>& pos, Graphe graphe2) {
    Token tok = this->token(pos);
    switch(tok.tok){
        case Token::EUCLIDE:
            eat(pos, tok);
            graphe2.euclide();
            break;
        case Token::MB:
            eat(pos, tok);
            graphe2.mb();
            break;
        case Token::PLUS:
            eat(pos, tok);
            graphe2.euclidePlus();
            break;
        default:
            break;
    }
    return graphe2;
}

void LParser::printGraph() {this->graphe.print();}

const map<int, map<char, int>> &LParser::getGraph() {return this->graphe.get();}


int main(){
    LParser lParser = LParser(".*https?");
    lParser.printGraph();
}