#include "LParser.hh"

int main(int argc, char* argv[]){
    if (argc > 1){
        LParser lParser = LParser(argv[1]);
        lParser.export_graphivz();
    }
    return 0;
}