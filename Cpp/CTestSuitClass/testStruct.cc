//
// Created by jules on 20/10/23.
//

#include "testStruct.hh"

struct testStruct addTest(int val, int exp, char *mes, struct testStruct testSuit)
{
    struct test *test = (struct test *)malloc(sizeof (struct test));
    test->val = val;
    test->exp = exp;
    test->mes = mes;
    if (testSuit.size == 0)
    {
        testSuit.first = test;
        testSuit.last = test;
    }
    else
        testSuit.last->next = test;
    testSuit.size += 1;
    test->next = NULL;
    return testSuit;
}

void launchTestSuit(struct testStruct testSuit)
{
    int success = 0;
    struct test *test = testSuit.first;
    struct test *tmp = NULL;
    int i = 0;
    while (i < testSuit.size)
    {
        if (test->val == test->exp)
            success++;
        else
            printf("[%s]: Failed: Expected %d but got %d\n", test->mes, test->exp, test->val);
        tmp = test;
        test = test->next;
        free(tmp);
        i++;
    }
    printf("\nResult: %d/%d\n", success, testSuit.size);
}

struct testStruct initTestSuit()
{
    struct testStruct testSuit;
    testSuit.size = 0;
    testSuit.last = NULL;
    testSuit.first = NULL;
    return testSuit;
}