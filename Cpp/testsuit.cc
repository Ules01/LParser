#include "CTestSuitClass/testStruct.hh"
#include "src/LParser.hh"

void basic(){
    struct testStruct testSuit = initTestSuit("Basic Serie");
    LParser lParser("a + b");
    testSuit = addTest(lParser.isaccept("a"), true, "Basic or: a in [a + b]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), true, "Basic or: b in [a + b]", testSuit);
    testSuit = addTest(lParser.isaccept("c"), false, "Basic or: c in [a + b]", testSuit);

    lParser = LParser("ab");
    testSuit = addTest(lParser.isaccept("a"), false, "Basic and: a in [ab]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), false, "Basic and: b in [ab]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), true, "Basic and: ab in [ab]", testSuit);
    testSuit = addTest(lParser.isaccept("abc"), false, "Basic and: abc in [ab]", testSuit);
    testSuit = addTest(lParser.isaccept("ba"), false, "Basic and: ba in [ab]", testSuit);

    lParser = LParser("a*");
    testSuit = addTest(lParser.isaccept(""), true, "Basic *: $ and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("a"), true, "Basic *: a and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("aaa"), true, "Basic *: aaa and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("aaca"), false, "Basic *: aaca and [a*]", testSuit);

    lParser = LParser("a!");
    testSuit = addTest(lParser.isaccept(""), false, "Basic !: $ and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("a"), true, "Basic !: a and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("aaa"), true, "Basic !: aaa and [a*]", testSuit);
    testSuit = addTest(lParser.isaccept("aaca"), false, "Basic !: aaca and [a*]", testSuit);

    lParser = LParser("a?");
    testSuit = addTest(lParser.isaccept(""), true, "Basic ?: $ and [a?]", testSuit);
    testSuit = addTest(lParser.isaccept("a"), true, "Basic ?: a and [a?]", testSuit);
    testSuit = addTest(lParser.isaccept("aa"), false, "Basic ?: aa and [a?]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), false, "Basic ?: b and [a?]", testSuit);

    lParser = LParser(".");
    testSuit = addTest(lParser.isaccept(""), false, "Basic .: $ and [.]", testSuit);
    testSuit = addTest(lParser.isaccept("a"), true, "Basic .: a and [.]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), true, "Basic .: b and [.]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), false, "Basic .: ab and [.]", testSuit);

    launchTestSuit(testSuit);
}

int main(void) {
    basic();

    LParser lParser("a+bc");
    lParser.export_graphivz();

    return 0;
}