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
        case '|':
            return {'|', Token::OR};
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
        case '+':
            return {'+', Token::PLUS};
        case '-':
            return {'-', Token::DASH};
        case '[':
            return {'[', Token::LBRACKET};
        case ']':
            return {']', Token::RBRACKET};
        default:
            return {(*(this->regexp + *pos)), Token::N};
    }
}

void LParser::eat(const shared_ptr<int>& pos, Token search){
    Token tok = this->token(pos);
    if (search != tok)
        LParser::misMatch(tok.c, search);
    *pos += 1;
}

void LParser::misMatch(char get, Token expect){
    cerr << "Syntax error: was expecting '" << expect.c << "' but get '" << get << "'" <<endl;
    throw (SYNTAX_ERROR);
}

ostream& operator<<(ostream& os, const LParser &lparser) {
    return os<<lparser.regexp << endl;
}

void LParser::Z(const shared_ptr<int>& pos) {
    Graphe graphe_tmp = this->S(pos, Graphe());
    this->eat(pos, {'$', Token::END});
    this->graphe = graphe_tmp.reduce();
    this->graphe = graphe_tmp;
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
        G = G.reduce();
        G = G.reduce_or();
    }
    return G;
}

Graphe LParser::D(const shared_ptr<int>& pos, Graphe G) {
    Token tok = this->token(pos);
    if (tok.tok == Token::DOT){
        this->eat(pos, tok);
        return G * '.';
    } else if (tok.tok == Token::LBRACKET) {
        this->eat(pos,tok);
        return G * this->F(pos, Graphe());
    } else {
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

Graphe LParser::F(const shared_ptr<int>& pos, Graphe G){
    Token tok = this->token(pos);
    if (tok.tok == Token::RBRACKET)
        return G;
    uint8_t prev = tok.c;
    uint8_t curr;
    this->eat(pos, {'n', Token::N});
    G = G * tok.c;
    tok = this->token(pos);
    while (tok.tok != Token::RBRACKET){
        if (tok.tok == Token::DASH){
            this->eat(pos, tok);
            tok = this->token(pos);
            this->eat(pos, {'n', Token::N});
            curr = tok.c;
            if (curr < prev){
                cerr << "Value error: " << (char)prev << " has a higher value than " << tok.c << endl;
                throw (VALUE_ERROR);
            }
            for (char c = prev + 1; c <= curr; c = c + 1) {
                G = G + (Graphe() * c);
            }
            prev = curr;
        } else{
            prev = tok.c;
            this->eat(pos, {'n', Token::N});
            G = G + (Graphe() * prev);
        }
        tok = this->token(pos);
    }
    this->eat(pos, {']', Token::RBRACKET});
    G = G.reduce();
    G = G.reduce_or();
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

pair<int, char *> LParser::subfound(const char* str, int pos){
    int size = sizeof(str);
    int states = 0;
    auto G = this->graphe.get();
    char c;
    int i = 0;
    char res[size];
    while (pos < size){
        c = str[pos + i];
        if (G[states].find(c) == G[states].end())
            return pair<int, char *>(-1, NULL);
        states = G[states][c];
        res[i] = c;
        if (this->graphe.inEnd(states)) {
            res[i + 1] = '\0';
            return pair<int, char *>(i + 1, res);
        }
        i += 1;
    }
    return pair<int, char*>(-1, NULL);
}

char *LParser::found(const char *str){
    int size = sizeof(str);
    pair<int, char *> res;
    for (int pos = 0; pos < size; pos++){
        res = this->subfound(str, pos);
        if (res.first > 0)
            return res.second;
    }
    if (this->graphe.inEnd(0)) {
        return (char *)"\0";
    }
    return NULL;
}

char *LParser::found(const char *str, size_t pos){
    int size = sizeof(str);
    pair<int, char *> res;
    for (; pos < size; pos++){
        res = this->subfound(str, pos);
        if (res.first > 0)
            return res.second;
    }
    return NULL;
}

vector<string> LParser::all_at(const char *str, size_t pos) {
    auto G = this->graphe.get();
    vector<string> res = vector<string>();
    string s = "";
    if (G[0].find(str[pos]) != G[0].end())
    {
        s = s + str[pos];
        pos += 1;
        if (this->graphe.inEnd(1))
            res.push_back(s);
    } else
        return res;
    int state = 1;
    for (; G[state].find(str[pos]) != G[state].end(); pos += 1){
        s = s + str[pos];
        if (this->graphe.inEnd(state))
            res.push_back(s);
    }
    return res;
}

vector<string> LParser::all(const char *str){
    if(str == NULL)
        return vector<string>();
    vector<string> res = vector<string>();
    if (this->graphe.inEnd(0))
        res.push_back("");
    vector<string> vec_s;
    for (size_t i = 0; str[i] != '\0';  i++){
        vec_s = all_at(str, i);
        if (vec_s.size() != 0){
            for (string s : vec_s){
                res.push_back(s);
            }
        }
    }
    return res;
}