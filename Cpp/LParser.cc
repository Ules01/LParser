#include "LParser.hh"

using namespace std;

LParser::LParser(char *regexp){
    this->regexp = regexp;
    this->graphe = Graphe();
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
    return os<<lparser.regexp << endl;
}

void LParser::Z(shared_ptr<int> pos) {
    Graphe graphe_tmp = this->S(pos);
    this->eat(pos, {'$', Token::END});
    this->graphe = graphe_tmp.reduce();
}

Graphe LParser::S(shared_ptr<int> pos) {
    Token tok = this->token(pos);
    if (not tok.in(vector<enum Token::tok>({Token::RPARA, Token::EUCLIDE, Token::MB, Token::PLUS, Token::OR, Token::END})))
        return this->A(pos);
    return Graphe();
}

Graphe LParser::A(shared_ptr<int> pos) {
    Graphe graphe2 = this->B(pos);
    graphe2 = this->C(pos, graphe2);
    Graphe graphe3 = this->S(pos);
    return graphe2 * graphe3;
}

Graphe LParser::B(shared_ptr<int> pos) {
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

Graphe LParser::C(shared_ptr<int> pos, Graphe graphe2) {
    Token tok = this->token(pos);
    if (tok.tok == Token::OR){
        this->eat(pos, tok);
        graphe2 + this->B(pos);
        graphe2 = this->C(pos, graphe2);
    }
    return graphe2;
}

Graphe LParser::D(shared_ptr<int> pos) {
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

Graphe LParser::E(shared_ptr<int> pos, Graphe graphe2) {
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



int main(){
    LParser lParser = LParser("a + b");

    auto G = lParser.graphe.get();
    for (const auto& link_1 : G){
        printf("%d:\n", link_1.first);
        for (auto link_2 : link_1.second){
            printf("\t%c -> %d\n", link_2.first, link_2.second);
        }
    }

}