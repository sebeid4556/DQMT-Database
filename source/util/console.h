#ifndef UTIL_CONOSLE_H_
#define UTIL_CONSOLE_H_

#include<stdio.h>
#include<stdlib.h>

#include"types.h"

#define CONSOLE_RED "\x1b[31m"
#define CONSOLE_GREEN "\x1b[32m"
#define CONSOLE_YELLOW "\x1b[33m"
#define CONSOLE_MAGENTA "\x1b[35m"
#define CONSOLE_CYAN "\x1b[36m"
#define CONSOLE_WHITE "\x1b[39m"
#define CONSOLE_OK "[ \x1b[32mOK\x1b[39m ]"

void GREEN(const CHAR *pStr);
void YELLOW(const CHAR *pStr);

CHAR *GREEN(CHAR *pStr);

void OK(const CHAR *pStr);
void FAIL();

#endif // UTIL_CONSOLE_H_