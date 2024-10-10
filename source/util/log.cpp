#include<string.h>

#include"log.h"
#include"error.h"

Log::Log(const CHAR *pPath)
{
    pFile = fopen(pPath, "w");
    if(!pFile)
    {
        fatalError("fopen() failed", "Log::Log");
    }
}

Log::~Log()
{
    fclose(pFile);
}

void Log::log(const CHAR *pFmt, ...)
{    
    CHAR out[MAX_LOG_LENGTH] = {NULL};

    std::va_list args;
    va_start(args, pFmt);

    INT32 i = 0;    //char count
    for(const CHAR *p = pFmt; *p != '\0'; p++)
    {
        if(i++ > MAX_LOG_LENGTH) break;
        switch(*p)
        {
            case '%':
                switch(*++p)
                {
                    case '0':
                        switch(*++p)
                        {
                            case '2':
                                if(*++p == 'X') sprintf(out, "%02X", va_arg(args, UINT8));
                        }
                        break;

                    case 'i':
                        sprintf(out, "%i", va_arg(args, INT32));
                        continue;
                    case 'f':
                        sprintf(out, "%f", va_arg(args, double));
                        continue;
                    case 's':
                        sprintf(out, "%s", va_arg(args, const CHAR *));
                        continue;
                    case 'c':
                        sprintf(out, "%c", va_arg(args, const CHAR));
                        continue;
                    case 'x':
                        sprintf(out, "%x", va_arg(args, UINT32));
                        continue;
                    case 'X':
                        sprintf(out, "%X", va_arg(args, UINT32));
                    case '%':
                        sprintf(out, "%%");
                        continue;
                }
                printf("[ERROR]: unknown format specifier %%c\n", (CHAR)*p);
                break;  //format error
            case '\n':
                continue;
            case '\t':
                continue;
        }
        sprintf(out, "%c", (CHAR)*p);
    }
    va_end(args);

    if(output_to_console)
    {
        printf(out);
    }

    fprintf(pFile, out);

}