#include<stdio.h>
#include<stdlib.h>

#include"types.h"
#include"error.h"

void LINE()
{
    printf("==================================================================\n");
}

void error(const CHAR *pMsg, const CHAR *pPrefix)
{
    LINE();
    printf("[!]ERROR: %s(): %s\n", pPrefix, pMsg);
    LINE();
}

void fatalError(const CHAR *pMsg)
{
    printf("[!]ERROR: %s\n", pMsg);
    exit(1);
}

void fatalError(const CHAR *pMsg, const CHAR *pPrefix)
{
    LINE();
    printf("[!]ERROR: %s(): %s\n", pPrefix, pMsg);
    LINE();
    exit(1);
}