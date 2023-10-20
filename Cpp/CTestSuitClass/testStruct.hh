#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct test{
    int exp;
    int val;
    char *mes;
    struct test *next;
};

struct testStruct {
    int size;
    struct test *first;
    struct test *last;
    char *title;
};

struct testStruct addTest(int val, int exp, char *mes, struct testStruct testSuit);
void launchTestSuit(struct testStruct testSuit);
struct testStruct initTestSuit(char *title);
