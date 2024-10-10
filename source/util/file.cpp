#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"types.h"
#include"file.h"
#include"error.h"

const CHAR *kFileErrorMessages[NUM_FILE_ERRORS] = 
{
    "path is too long",
    "invalid path",
    "fopen() failed",
    "fread() failed"
};

INT32 loadFileIntoBuffer(CHAR *pPath, UINT8 **pBuffer, UINT32 *pSize)
{
    printf("[+]Loading %s...", pPath);

    //check path
    UINT32 len = strlen(pPath);
    if(len == 0) return FILE_ERROR_PATH_INVALID;
    else if(len > MAX_PATH) return FILE_ERROR_PATH_TOO_LONG;

    //open file
    FILE *pFp = fopen(pPath, "rb");
    if(!pFp)
    {
        perror(NULL);
        return FILE_ERROR_FOPEN_FAILED;
    }
    
    //get size    
    int res = fseek(pFp, 0, SEEK_END);    
    if(res != 0)
    {        
        fatalError("fseek() failed\n", "loadFileIntoBuffer");
        perror(NULL);
    }
    UINT32 size = ftell(pFp); 
    rewind(pFp);
    *pSize = size;    

    //read file into buffer    
    *pBuffer = (UINT8 *)malloc(size);     
    INT32 r = fread(*pBuffer, 1, size, pFp);    
    if(r == 0) return FILE_ERROR_FREAD_FAILED;
    
    fclose(pFp);

    printf("Done.\n");

    return FILE_RET_OK;
}

