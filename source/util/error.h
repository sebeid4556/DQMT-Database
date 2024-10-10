#ifndef UTIL_ERROR_H_
#define UTIL_ERROR_H_

#include"types.h"

void LINE();

void error(const CHAR *pMsg, const CHAR *pPrefix);

void fatalError(const CHAR *pMsg);
void fatalError(const CHAR *pMsg, const CHAR *pPrefix);

#endif // UTIL_ERROR_H_