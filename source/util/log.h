#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

#include<stdio.h>
#include<cstdarg>

#include"types.h"

//WORK IN PROGRESS

class Log
{
    public:
        UINT32 MAX_LOG_LENGTH = 256;

        Log(const CHAR *pPath);
        ~Log();
        void log(const CHAR *pFmt, ...);
        void setOutputToTerminal(bool flag);
    private:
        bool output_to_console = false;
        FILE *pFile;
};

#endif // UTIL_LOG_H_