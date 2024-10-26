#include<stdio.h>
#include<stdlib.h>

#include"types.h"
#include"error.h"
#include"log.h"

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
    LINE();
    printf("[!]ERROR: %s\n", pMsg);
    LINE();
    throw("wtf");   //for gdb
    exit(1);
}

void fatalError(const CHAR *pMsg, const CHAR *pPrefix)
{
    LINE();
    printf("[!]ERROR: %s(): %s\n", pPrefix, pMsg);
    LINE();
    throw("wtf");   //for gdb
    exit(1);
}