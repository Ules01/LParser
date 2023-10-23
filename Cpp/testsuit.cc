#include "CTestSuitClass/testStruct.hh"
#include "src/LParser.hh"

int basic(){
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

    return launchTestSuit(testSuit);
}

int semi_advanced(void){
    struct testStruct testSuit = initTestSuit("Semi advanced");


    LParser lParser = LParser("a + bc");
    testSuit = addTest(lParser.isaccept("a"), false, "Semi advanced or and: a and [a + bc]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), false, "Semi advanced or and: b and [a + bc]", testSuit);
    testSuit = addTest(lParser.isaccept("c"), false, "Semi advanced or and: c and [a + bc]", testSuit);
    testSuit = addTest(lParser.isaccept("ac"), true, "Semi advanced or and: ac and [a + bc]", testSuit);
    testSuit = addTest(lParser.isaccept("bc"), true, "Semi advanced or and: bc and [a + bc]", testSuit);
    testSuit = addTest(lParser.isaccept("ca"), false, "Semi advanced or and: ca and [a + bc]", testSuit);


    lParser = LParser("(ab) + c");
    testSuit = addTest(lParser.isaccept("ac"), false, "Semi advanced (and) or: ac in [(ab) + c]", testSuit);
    testSuit = addTest(lParser.isaccept("abc"), false, "Semi advanced (and) or: abc in [(ab) + c]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), true, "Semi advanced (and) or: ab in [(ab) + c]", testSuit);
    testSuit = addTest(lParser.isaccept("c"), true, "Semi advanced (and) or: c in [(ab) + c]", testSuit);

    lParser = LParser("ab*");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced and *: a in [ab*]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), true, "Semi advanced and *: ab in [ab*]", testSuit);
    testSuit = addTest(lParser.isaccept("abbbb"), true, "Semi advanced and *: abbbb in [ab*]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), false, "Semi advanced and *: b in [ab*]", testSuit);
    testSuit = addTest(lParser.isaccept(""), false, "Semi advanced and *: $ in [ab*]", testSuit);

    lParser = LParser("(ab)*");
    testSuit = addTest(lParser.isaccept("a"), false, "Semi advanced and *: a in [(ab)*]", testSuit);
    testSuit = addTest(lParser.isaccept("aba"), false, "Semi advanced and *: aba in [(ab)*]", testSuit);
    testSuit = addTest(lParser.isaccept(""), true, "Semi advanced and *: $ in [(ab)*]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), true, "Semi advanced and *: ab in [(ab)*]", testSuit);
    testSuit = addTest(lParser.isaccept("ababab"), true, "Semi advanced and *: ababab in [(ab)*]", testSuit);

    lParser = LParser("(a + b)*");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced (or)*: a in [(a + b)*]", testSuit);
    testSuit = addTest(lParser.isaccept("abababbbabba"), true, "Semi advanced (or)*: abababbbabba in [(a + b)*]", testSuit);
    testSuit = addTest(lParser.isaccept("bbbbbbb"), true, "Semi advanced (or)*: bbbbbbb in [(a + b)*]", testSuit);
    testSuit = addTest(lParser.isaccept(""), true, "Semi advanced (or)*: $ in [(a + b)*]", testSuit);
    testSuit = addTest(lParser.isaccept("c"), false, "Semi advanced (or)*: c in [(a + b)*]", testSuit);

    lParser = LParser("a + b*");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced or *: a in [a + b*]", testSuit);
    testSuit = addTest(lParser.isaccept(""), true, "Semi advanced or *: $ in [a + b*]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), true, "Semi advanced or *: b in [a + b*]", testSuit);
    testSuit = addTest(lParser.isaccept("bbbb"), true, "Semi advanced or *: bbb in [a + b*]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), false, "Semi advanced or *: ab in [a + b*]", testSuit);
    testSuit = addTest(lParser.isaccept("ba"), false, "Semi advanced or *: ba in [a + b*]", testSuit);


    lParser = LParser("(a + b)!");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced (or)!: a in [(a + b)!]", testSuit);
    testSuit = addTest(lParser.isaccept("abababbbabba"), true, "Semi advanced (or)!: abababbbabba in [(a + b)!]", testSuit);
    testSuit = addTest(lParser.isaccept("bbbbbbb"), true, "Semi advanced (or)!: bbbbbbb in [(a + b)!]", testSuit);
    testSuit = addTest(lParser.isaccept(""), false, "Semi advanced (or)!: $ in [(a + b)!]", testSuit);
    testSuit = addTest(lParser.isaccept("c"), false, "Semi advanced (or)!: c in [(a + b)!]", testSuit);

    lParser = LParser("a + b!");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced or !: a in [a + b!]", testSuit);
    testSuit = addTest(lParser.isaccept(""), false, "Semi advanced or !: $ in [a + b!]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), true, "Semi advanced or !: b in [a + b!]", testSuit);
    testSuit = addTest(lParser.isaccept("bbbb"), true, "Semi advanced or !: bbb in [a + b!]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), false, "Semi advanced or !: ab in [a + b!]", testSuit);
    testSuit = addTest(lParser.isaccept("ba"), false, "Semi advanced or !: ba in [a + b!]", testSuit);

    lParser = LParser("a+b?");
    testSuit = addTest(lParser.isaccept("a"), true, "Semi advanced or ?: a in [a + b?]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), true, "Semi advanced or ?: b in [a + b?]", testSuit);
    testSuit = addTest(lParser.isaccept(""), true, "Semi advanced or ?: $ in [a + b?]", testSuit);
    testSuit = addTest(lParser.isaccept("ab"), false, "Semi advanced or ?: ab in [a + b?]", testSuit);

    lParser = LParser("ab?c");
    testSuit = addTest(lParser.isaccept("ac"), true, "Semi advanced and ?: ab in [ab?]", testSuit);
    testSuit = addTest(lParser.isaccept("ac"), true, "Semi advanced and ?: a in [ab?]", testSuit);
    testSuit = addTest(lParser.isaccept("b"), false, "Semi advanced and ?: b in [ab?]", testSuit);

    return launchTestSuit(testSuit);
}

int advanced() {
    struct testStruct testSuit = initTestSuit("Advanced");

    LParser lParser = LParser("((a+b+c)d)*");
    testSuit = addTest(lParser.isaccept("adadcd"), true, "Advanced (or) and *: adadcd in [(a + b + c) d*", testSuit);
    testSuit = addTest(lParser.isaccept("adacd"), false, "Advanced (or) and *: adacd in [(a + b + c) d*", testSuit);
    testSuit = addTest(lParser.isaccept("adadcd"), true, "Advanced (or) and *: adadc in [(a + b + c) d*", testSuit);

    lParser = LParser("(chialer)+(crever)+(mourir)+(caner)+(manger)");
    testSuit = addTest(lParser.isaccept("mourir"), true, "Advanced (and)+(and)...: mourir in [(chialer)+(crever)+(mourir)+(caner)+(manger)]", testSuit);

    lParser = LParser("(ab?c)+(acb)");
    testSuit = addTest(lParser.isaccept("abc"), true, "Advanced (?)+(and)...: abc in [(ab?c)+(acb)]", testSuit);
    testSuit = addTest(lParser.isaccept("ac"), true, "Advanced (?)+(and)...: ac in [(ab?c)+(acb)]", testSuit);
    testSuit = addTest(lParser.isaccept("acb"), true, "Advanced (?)+(and)...: acb in [(ab?c)+(acb)]", testSuit);
    testSuit = addTest(lParser.isaccept("abcb"), false, "Advanced (?)+(and)...: abcb in [(ab?c)+(acb)]", testSuit);


    launchTestSuit(testSuit);

}

int main(void) {
    int res = basic();
    res = res && semi_advanced();
    res = res && advanced();
    if (res)
        return 0;
    return -1;
}