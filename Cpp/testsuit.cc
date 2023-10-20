#include "CTestSuitClass/testStruct.hh"
#include "src/LParser.hh"

int main(void) {
    struct testStruct testSuit = initTestSuit();

    LParser lParser("a + b");
    testSuit = addTest(lParser.isaccept("a"), true, "Basi test: must be accepted", testSuit);
    launchTestSuit(testSuit);
}