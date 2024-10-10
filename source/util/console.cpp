#include<stdio.h>
#include<stdlib.h>

#include"console.h"

void GREEN(const CHAR *pStr)
{
    printf("\x1b[32m%s\x1b[39m", pStr);
}

void YELLOW(const CHAR *pStr)
{
    printf("\x1b[33m%s\x1b[39m", pStr);
}

void OK(const CHAR *pStr)
{
    printf("%s%s\n", CONSOLE_OK, pStr);
    //printf("[ %sOK%s ]\n", CONSOLE_GREEN, CONSOLE_WHITE);
}