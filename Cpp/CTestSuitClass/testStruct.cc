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
    else {
        testSuit.last->next = test;
        testSuit.last = test;
    }
    testSuit.size += 1;
    test->next = NULL;
    return testSuit;
}

int launchTestSuit(struct testStruct testSuit)
{
    printf("_________________________________\n%s:\n", testSuit.title);
    int success = 0;
    struct test *test = testSuit.first;
    struct test *tmp = NULL;
    int i = 0;
    while (i < testSuit.size)
    {
        if (test->val == test->exp)
            success++;
        else
            printf("\tFailed: Expected %d but got %d\n", test->mes, test->exp, test->val);
        tmp = test;
        test = test->next;
        free(tmp);
        i++;
    }
    printf("\n\tResult: %d/%d\n_________________________________\n", success, testSuit.size);
    return testSuit.size == success;
}

struct testStruct initTestSuit(char *title)
{
    struct testStruct testSuit;
    testSuit.size = 0;
    testSuit.last = NULL;
    testSuit.first = NULL;
    testSuit.title = title;
    return testSuit;
}